#include "board_config.h"
#include "network_config.h"
#include "system_globals.h"
#include "ldstl26_lidar.h"
#include "camsense_lidar.h"
#include "lidar_detection.h"
#include "msg/lidar_msg.h"
#include "esp_log.h"

static const char* TAG = "LIDAR_TASK";
namespace board_cfg = leap_config::board;
namespace net_cfg = leap_config::network;

static int baud_rate(LidarModel model) {
    return model == LidarModel::kStl26 ? net_cfg::kLidarBaudRate : net_cfg::kCamsenseLidarBaudRate;
}

static const char* model_name(LidarModel model) {
    return model == LidarModel::kStl26 ? "LD STL26" : "Camsense";
}

static uint32_t now_ms() {
    return static_cast<uint32_t>(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static void publish_scan(const LidarPoint* points, uint16_t count) {
    LidarMsg message = {};
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
    ESP_LOGI(TAG, "Auto-detect lidar on UART%d RX=%d: STL26=%d, Camsense=%d baud",
             static_cast<int>(net_cfg::kLidarUartPort), static_cast<int>(board_cfg::kLidarRxPin),
             net_cfg::kLidarBaudRate, net_cfg::kCamsenseLidarBaudRate);

    while (1) {
        uint16_t count = 0;
        const LidarModel previous = detection.DetectedModel();
        const bool probe_stl26 = detection.ProbeModel() == LidarModel::kStl26;
        const bool completed = probe_stl26 ? stl26.Poll(points, &count) : camsense.Poll(points, &count);
        const uint32_t packets = probe_stl26 ? stl26.ValidPacketCount() : camsense.ValidPacketCount();
        if (detection.Update(now_ms(), packets)) {
            if (previous != LidarModel::kUnknown) {
                ESP_LOGW(TAG, "%s data timeout; restarting detection", model_name(previous));
                publish_scan(nullptr, 0);
            }
            ESP_ERROR_CHECK(uart_set_baudrate(net_cfg::kLidarUartPort, baud_rate(detection.ProbeModel())));
            ESP_ERROR_CHECK(uart_flush_input(net_cfg::kLidarUartPort));
            stl26.Reset();
            camsense.Reset();
            ESP_LOGI(TAG, "Probing %s at %d baud", model_name(detection.ProbeModel()),
                     baud_rate(detection.ProbeModel()));
        } else if (detection.DetectedModel() != LidarModel::kUnknown) {
            if (previous == LidarModel::kUnknown) {
                ESP_LOGI(TAG, "Detected %s at %d baud", model_name(detection.DetectedModel()),
                         baud_rate(detection.DetectedModel()));
            }
            if (completed) {
                publish_scan(points, count);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(net_cfg::kLidarTaskPeriodMs));
    }
}
