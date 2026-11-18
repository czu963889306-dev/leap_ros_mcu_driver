#include "board_config.h"
#include "network_config.h"
#include "system_globals.h"
#include "ldstl26_lidar.h"
#include "camsense_lidar.h"
#include "lidar_detection.h"
#include "msg/lidar_msg.h"
#include "driver/ledc.h"
#include "esp_log.h"

static const char* TAG = "LIDAR_TASK";
namespace board_cfg = leap_config::board;
namespace net_cfg = leap_config::network;

// Timer 0 and channels 0–3 are used by the chassis motors.
static constexpr ledc_mode_t kPwmMode = LEDC_LOW_SPEED_MODE;
static constexpr ledc_timer_t kPwmTimer = LEDC_TIMER_1;
static constexpr ledc_channel_t kPwmChannel = LEDC_CHANNEL_7;
static constexpr ledc_timer_bit_t kPwmResolution = LEDC_TIMER_8_BIT;
static constexpr uint32_t kPwmFullDuty = 1U << kPwmResolution;
static constexpr uint32_t kPwmStartupDuty = kPwmFullDuty / 2;
static constexpr uint32_t kPwmStartupHoldMs = 200;
static constexpr uint32_t kPwmControlPeriodMs = 1000;
static constexpr uint32_t kPwmStep = 5;
static constexpr uint32_t kPwmMinDuty = kPwmFullDuty / 20;
static constexpr uint32_t kPwmMaxDuty = kPwmFullDuty * 95 / 100;
static constexpr uint32_t kLidarSpeedTolerance = 36;

static void start_lidar_pwm() {
    ledc_timer_config_t timer_config = {};
    timer_config.speed_mode = kPwmMode;
    timer_config.duty_resolution = kPwmResolution;
    timer_config.timer_num = kPwmTimer;
    timer_config.freq_hz = board_cfg::kLidarPwmFrequencyHz;
    timer_config.clk_cfg = LEDC_AUTO_CLK;
    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    ledc_channel_config_t channel_config = {};
    channel_config.gpio_num = board_cfg::kLidarPwmPin;
    channel_config.speed_mode = kPwmMode;
    channel_config.channel = kPwmChannel;
    channel_config.timer_sel = kPwmTimer;
    // LD14-style controllers latch external speed control at about 50% duty.
    channel_config.duty = kPwmStartupDuty;
    ESP_ERROR_CHECK(ledc_channel_config(&channel_config));
}

static void set_lidar_pwm_duty(uint32_t duty) {
    ESP_ERROR_CHECK(ledc_set_duty(kPwmMode, kPwmChannel, duty));
    ESP_ERROR_CHECK(ledc_update_duty(kPwmMode, kPwmChannel));
    ESP_LOGI(TAG, "Motor PWM on GPIO%d: %lu Hz, %.1f%% duty",
             static_cast<int>(board_cfg::kLidarPwmPin),
             static_cast<unsigned long>(board_cfg::kLidarPwmFrequencyHz),
             100.0 * duty / kPwmFullDuty);
}

static int baud_rate(LidarModel model) {
    return model == LidarModel::kStl26 ? net_cfg::kLidarBaudRate : net_cfg::kCamsenseLidarBaudRate;
}

static const char* model_name(LidarModel model) {
    return model == LidarModel::kStl26 ? "LD STL26" : "Camsense";
}

static uint32_t now_ms() {
    return static_cast<uint32_t>(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static void publish_scan(const LidarPoint* points, uint16_t count, uint16_t speed_deg_per_sec) {
    LidarMsg message = {};
    message.speed_deg_per_sec = speed_deg_per_sec;
    for (uint16_t i = 0; i < count; ++i) {
        const int angle = LidarMirroredAngle(points[i].angle);
        const uint16_t distance = static_cast<uint16_t>(points[i].distance);
        if (distance > 0 && (message.distances[angle] == 0 || distance < message.distances[angle])) {
            message.distances[angle] = distance;
        }
    }
    xQueueOverwrite(system_globals().queues.lidar_state, &message);
    system_globals().flags.lidar_scan_sequence = system_globals().flags.lidar_scan_sequence + 1;
}

void lidar_task(void *p) {
    start_lidar_pwm();

    // One UART owner; parsers never install or reconfigure the shared port.
    uart_config_t config = {};
    config.baud_rate = net_cfg::kLidarBaudRate;
    config.data_bits = UART_DATA_8_BITS;
    config.parity = UART_PARITY_DISABLE;
    config.stop_bits = UART_STOP_BITS_1;
    config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    config.source_clk = UART_SCLK_DEFAULT;
    ESP_ERROR_CHECK(uart_driver_install(net_cfg::kLidarUartPort, 4096, 0, 0, nullptr, 0));
    ESP_ERROR_CHECK(uart_param_config(net_cfg::kLidarUartPort, &config));
    ESP_ERROR_CHECK(uart_set_pin(net_cfg::kLidarUartPort, board_cfg::kLidarTxPin,
                                board_cfg::kLidarRxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    static Ldstl26Lidar stl26(net_cfg::kLidarUartPort, board_cfg::kLidarTxPin, board_cfg::kLidarRxPin);
    static CamsenseLidar camsense(net_cfg::kLidarUartPort, board_cfg::kLidarTxPin, board_cfg::kLidarRxPin);
    static LidarPoint points[MAX_LIDAR_POINTS_PER_SCAN];
    LidarDetection detection(net_cfg::kLidarProbePeriodMs, net_cfg::kLidarDisconnectTimeoutMs,
                             net_cfg::kLidarDetectionMinPackets);
    detection.Begin(now_ms());
    uint32_t stl26_detected_ms = 0;
    uint32_t last_control_ms = 0;
    uint32_t pwm_duty = kPwmStartupDuty;
    uint32_t last_control_packets = 0;
    ESP_LOGI(TAG, "Auto-detect lidar on UART%d RX=%d: STL26=%d, Camsense=%d baud",
             static_cast<int>(net_cfg::kLidarUartPort), static_cast<int>(board_cfg::kLidarRxPin),
             net_cfg::kLidarBaudRate, net_cfg::kCamsenseLidarBaudRate);

    while (1) {
        uint16_t count = 0;
        const LidarModel previous = detection.DetectedModel();
        const bool probe_stl26 = detection.ProbeModel() == LidarModel::kStl26;
        const bool completed = probe_stl26 ? stl26.Poll(points, &count) : camsense.Poll(points, &count);
        const uint32_t packets = probe_stl26 ? stl26.ValidPacketCount() : camsense.ValidPacketCount();
        const uint32_t current_ms = now_ms();
        if (detection.Update(current_ms, packets)) {
            if (previous != LidarModel::kUnknown) {
                ESP_LOGW(TAG, "%s data timeout; restarting detection", model_name(previous));
                publish_scan(nullptr, 0, 0);
            }
            ESP_ERROR_CHECK(uart_set_baudrate(net_cfg::kLidarUartPort, baud_rate(detection.ProbeModel())));
            ESP_ERROR_CHECK(uart_flush_input(net_cfg::kLidarUartPort));
            stl26.Reset();
            camsense.Reset();
            ESP_LOGI(TAG, "Probing %s at %d baud", model_name(detection.ProbeModel()),
                     baud_rate(detection.ProbeModel()));
        } else if (detection.DetectedModel() != LidarModel::kUnknown) {
            if (previous == LidarModel::kUnknown) {
                stl26_detected_ms = current_ms;
                ESP_LOGI(TAG, "Detected %s at %d baud", model_name(detection.DetectedModel()),
                         baud_rate(detection.DetectedModel()));
            }
            if (completed) {
                publish_scan(points, count, probe_stl26 ? stl26.SpeedDegPerSec() : 0);
            }
        }
        // Maintain the activation waveform until the radar starts sending valid frames.
        if (detection.DetectedModel() != LidarModel::kStl26) {
            if (pwm_duty != kPwmStartupDuty) {
                pwm_duty = kPwmStartupDuty;
                set_lidar_pwm_duty(pwm_duty);
            }
            last_control_packets = 0;
            last_control_ms = current_ms;
        } else if (current_ms - stl26_detected_ms >= kPwmStartupHoldMs &&
                   current_ms - last_control_ms >= kPwmControlPeriodMs &&
                   packets != last_control_packets && stl26.SpeedDegPerSec() > 0) {
            const uint32_t speed = stl26.SpeedDegPerSec();
            uint32_t new_duty = pwm_duty;
            if (speed + kLidarSpeedTolerance < board_cfg::kLidarTargetSpeedDegPerSec &&
                pwm_duty < kPwmMaxDuty) {
                new_duty = pwm_duty + kPwmStep > kPwmMaxDuty ? kPwmMaxDuty : pwm_duty + kPwmStep;
            } else if (speed > board_cfg::kLidarTargetSpeedDegPerSec + kLidarSpeedTolerance &&
                       pwm_duty > kPwmMinDuty) {
                new_duty = pwm_duty - kPwmStep < kPwmMinDuty ? kPwmMinDuty : pwm_duty - kPwmStep;
            }
            if (new_duty != pwm_duty) {
                pwm_duty = new_duty;
                set_lidar_pwm_duty(pwm_duty);
            }
            last_control_ms = current_ms;
            last_control_packets = packets;
        }
        vTaskDelay(pdMS_TO_TICKS(net_cfg::kLidarTaskPeriodMs));
    }
}
