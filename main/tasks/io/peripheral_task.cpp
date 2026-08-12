#include "system_globals.h"
#include "app_runtime.h"
#include "board.h"
#include "wifi_app.h"
#include "msg/servo_msg.h"
#include "msg/temperature_msg.h"

#include "driver/temperature_sensor.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "PERIPHERAL";
static const TickType_t kBootWifiResetLongPressTicks = pdMS_TO_TICKS(3000);
static const TickType_t kTemperatureSampleTicks = pdMS_TO_TICKS(1000);

static bool clear_wifi_for_provisioning() {
    const esp_err_t err = wifi_clear_sta_credentials();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to clear Wi-Fi credentials: %s", esp_err_to_name(err));
        return false;
    }

    status_led.SetMode(StatusLedMode::kFastBlink);
    ESP_LOGW(TAG, "Wi-Fi credentials cleared. Release BOOT to restart into provisioning mode.");
    return true;
}

static temperature_sensor_handle_t init_temperature_sensor() {
    temperature_sensor_handle_t sensor = nullptr;
    temperature_sensor_config_t config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(-10, 80);

    esp_err_t err = temperature_sensor_install(&config, &sensor);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Failed to install internal temperature sensor: %s", esp_err_to_name(err));
        return nullptr;
    }

    err = temperature_sensor_enable(sensor);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Failed to enable internal temperature sensor: %s", esp_err_to_name(err));
        temperature_sensor_uninstall(sensor);
        return nullptr;
    }

    return sensor;
}

static void sample_temperature_sensor(temperature_sensor_handle_t sensor) {
    if (sensor == nullptr || q_temperature_state == nullptr) {
        return;
    }

    TemperatureMsg msg = {};
    esp_err_t err = temperature_sensor_get_celsius(sensor, &msg.celsius);
    msg.valid = (err == ESP_OK);
    if (!msg.valid) {
        ESP_LOGW(TAG, "Failed to read internal temperature: %s", esp_err_to_name(err));
    }
    xQueueOverwrite(q_temperature_state, &msg);
}

void peripheral_task(void *p) {
    ServoMsg servo_cmd = {45.0f};
    TickType_t press_start_tick = 0;
    TickType_t last_temperature_sample_tick = 0;
    bool wifi_reset_requested = false;
    temperature_sensor_handle_t temperature_sensor = init_temperature_sensor();

    my_servo.SetAngle(servo_cmd.angle);
    
    while (1) {
        if (xQueueReceive(q_servo_cmd, &servo_cmd, 0) == pdTRUE) {
            my_servo.SetAngle(servo_cmd.angle);
        }

        const TickType_t now = xTaskGetTickCount();
        if ((now - last_temperature_sample_tick) >= kTemperatureSampleTicks) {
            last_temperature_sample_tick = now;
            sample_temperature_sensor(temperature_sensor);
        }

        status_led.Update(now);
        const bool button_state_changed = io0_button.Update();
        const bool button_pressed = io0_button.IsPressed();

        if (button_state_changed) {
            if (button_pressed) {
                press_start_tick = now;
                wifi_reset_requested = false;
            } else {
                if (wifi_reset_requested) {
                    ESP_LOGW(TAG, "Restarting after BOOT Wi-Fi reset.");
                    app_runtime_restart_after_delay_ms(200);
                }
                press_start_tick = 0;
                wifi_reset_requested = false;
            }
        }

        if (button_pressed &&
            press_start_tick != 0 &&
            !wifi_reset_requested &&
            (now - press_start_tick) >= kBootWifiResetLongPressTicks) {
            wifi_reset_requested = clear_wifi_for_provisioning();
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
