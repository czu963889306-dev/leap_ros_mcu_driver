#include "system_globals.h"
#include "mavlink_common.h"

#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stddef.h>
#include <stdint.h>

static const char *TAG = "MAVLINK_UART";

static constexpr uart_port_t kMavlinkUartPort = UART_NUM_0;
static constexpr gpio_num_t kMavlinkUartTxPin = GPIO_NUM_43;
static constexpr gpio_num_t kMavlinkUartRxPin = GPIO_NUM_44;
static constexpr int kMavlinkUartBaudRate = 230400;
static constexpr size_t kMavlinkUartRxBufferSize = 2048;
static constexpr size_t kMavlinkUartTxBufferSize = 8192;
static constexpr size_t kMavlinkReadBufferSize = 256;

struct UartMavlinkTransportContext {
    uart_port_t port;
};

static void WriteUartMavlinkBytes(const uint8_t *data, size_t len, void *ctx) {
    UartMavlinkTransportContext *uart = static_cast<UartMavlinkTransportContext *>(ctx);
    if (uart == nullptr || data == nullptr || len == 0) {
        return;
    }

    size_t tx_free = 0;
    if (uart_get_tx_buffer_free_size(uart->port, &tx_free) != ESP_OK || tx_free < len) {
        return;
    }

    uart_write_bytes(
        uart->port,
        reinterpret_cast<const char *>(data),
        static_cast<size_t>(len));
}

static esp_err_t InitMavlinkUart(void) {
    const uart_config_t uart_config = {
        .baud_rate = kMavlinkUartBaudRate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = {},
    };

    const bool driver_already_installed = uart_is_driver_installed(kMavlinkUartPort);
    esp_err_t err = ESP_OK;
    if (!driver_already_installed) {
        err = uart_driver_install(
            kMavlinkUartPort,
            kMavlinkUartRxBufferSize,
            kMavlinkUartTxBufferSize,
            0,
            nullptr,
            0);
        if (err != ESP_OK) {
            return err;
        }
    }

    err = uart_param_config(kMavlinkUartPort, &uart_config);
    if (err != ESP_OK) {
        if (!driver_already_installed) {
            uart_driver_delete(kMavlinkUartPort);
        }
        return err;
    }

    err = uart_set_pin(
        kMavlinkUartPort,
        kMavlinkUartTxPin,
        kMavlinkUartRxPin,
            UART_PIN_NO_CHANGE,
            UART_PIN_NO_CHANGE);
    if (err != ESP_OK) {
        if (!driver_already_installed) {
            uart_driver_delete(kMavlinkUartPort);
        }
        return err;
    }

    uart_flush_input(kMavlinkUartPort);
    return ESP_OK;
}

void mavlink_uart_task(void *pvParameters) {
    (void)pvParameters;

    const esp_err_t err = InitMavlinkUart();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init UART%d: %s",
                 static_cast<int>(kMavlinkUartPort),
                 esp_err_to_name(err));
        vTaskDelete(nullptr);
        return;
    }

    ESP_LOGI(TAG, "MAVLink UART started on UART%d, baud=%d",
             static_cast<int>(kMavlinkUartPort),
             kMavlinkUartBaudRate);

    uint8_t rx_buffer[kMavlinkReadBufferSize] = {};
    mavlink_message_t rx_msg = {};
    mavlink_status_t uart_status = {};
    MavlinkPublishState publish_state = {};

    UartMavlinkTransportContext uart_ctx = {
        .port = kMavlinkUartPort,
    };
    MavlinkTransport uart_transport = {
        .write = WriteUartMavlinkBytes,
        .ctx = &uart_ctx,
    };

    TickType_t last_wake_time = xTaskGetTickCount();
    const TickType_t frequency = pdMS_TO_TICKS(20);

    while (true) {
        const bool uart_enabled = g_wifi_comm_mode == WifiCommMode::kMavlinkUart;
        if (uart_enabled) {
            const int len = uart_read_bytes(
                kMavlinkUartPort,
                rx_buffer,
                sizeof(rx_buffer),
                0);
            if (len > 0) {
                for (int i = 0; i < len; ++i) {
                    if (mavlink_parse_char(MAVLINK_COMM_1, rx_buffer[i], &rx_msg, &uart_status)) {
                        mavlink_common_handle_message(
                            &rx_msg,
                            &uart_transport,
                            MavlinkTransportSource::kUart);
                    }
                }
            }

            mavlink_common_publish(&uart_transport, 1, &publish_state);
        }

        vTaskDelayUntil(&last_wake_time, frequency);
    }
}
