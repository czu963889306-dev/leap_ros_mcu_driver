#include "board_config.h"
#include "system_globals.h"
#include "board.h"
#include "msg/battery_msg.h"

#include "esp_log.h"

static const char *TAG = "BATTERY_TASK";
static constexpr TickType_t kBatterySampleTicks = pdMS_TO_TICKS(leap_config::board::kBatterySamplePeriodMs);

void battery_task(void *p) {
    (void)p;

    if (battery_adc.Init() != ESP_OK) {
        ESP_LOGE(TAG, "battery ADC init failed");
        vTaskDelete(NULL);
        return;
    }

    while (1) {
        BatteryAdcReading reading = battery_adc.Read();
        BatteryMsg msg = {};
        msg.adc_voltage_v = reading.adc_voltage_v;
        msg.voltage_v = reading.battery_voltage_v;
        msg.percentage = reading.percentage;
        msg.raw = reading.raw;
        msg.valid = reading.valid;
        if (system_globals().queues.battery_state != nullptr) {
            xQueueOverwrite(system_globals().queues.battery_state, &msg);
        }
        vTaskDelay(kBatterySampleTicks);
    }
}
