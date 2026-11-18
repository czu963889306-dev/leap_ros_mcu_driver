#include "ldstl26_lidar.h"
#include "esp_log.h"
#include <string.h>

static const char* TAG = "LDSTL26";

Ldstl26Lidar::Ldstl26Lidar(uart_port_t uart_num, gpio_num_t tx_pin, gpio_num_t rx_pin, int baud_rate)
    : uart_num_(uart_num), tx_pin_(tx_pin), rx_pin_(rx_pin), baud_rate_(baud_rate) {}

void Ldstl26Lidar::Init() {
    uart_config_t cfg = {};
    cfg.baud_rate = baud_rate_;
    cfg.data_bits = UART_DATA_8_BITS;
    cfg.parity = UART_PARITY_DISABLE;
    cfg.stop_bits = UART_STOP_BITS_1;
    cfg.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    cfg.source_clk = UART_SCLK_DEFAULT;

    ESP_ERROR_CHECK(uart_driver_install(uart_num_, 2048, 0, 0, nullptr, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num_, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(uart_num_, tx_pin_, rx_pin_, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_LOGI(TAG, "UART%d %d", uart_num_, baud_rate_);
}

void Ldstl26Lidar::Reset() {
    state_ = 0;
    packet_idx_ = 0;
    valid_packet_count_ = 0;
    speed_deg_per_sec_ = 0;
    scan_.Reset();
}

bool Ldstl26Lidar::Poll(LidarPoint* out_scan, uint16_t* out_count) {
    size_t available = 0;
    uart_get_buffered_data_len(uart_num_, &available);
    if (!available) return false;
    if (available > 512) available = 512;

    uint8_t buf[512];
    int len = uart_read_bytes(uart_num_, buf, available, 0);
    bool completed = false;

    for (int i = 0; i < len; i++)
        if (ProcessByte(buf[i], out_scan, out_count))
            completed = true;

    return completed;
}

bool Ldstl26Lidar::ProcessByte(uint8_t data, LidarPoint* out_scan, uint16_t* out_count) {
    if (state_ == 0) {
        if (data == 0x54) {
            packet_[0] = data;
            packet_idx_ = 1;
            state_ = 1;
        }
        return false;
    }

    if (state_ == 1) {
        if (data == 0x2C) {
            packet_[packet_idx_++] = data;
            state_ = 2;
        } else if (data == 0x54) {
            packet_[0] = data;
            packet_idx_ = 1;
        } else {
            state_ = 0;
        }
        return false;
    }

    packet_[packet_idx_++] = data;
    if (packet_idx_ < LDSTL26_PACKET_SIZE) return false;

    state_ = 0;
    packet_idx_ = 0;

    if (CRC8(packet_, 46) != packet_[46]) return false;
    const uint16_t start = packet_[4] | (packet_[5] << 8);
    const uint16_t end = packet_[42] | (packet_[43] << 8);
    if (start > 36000 || end > 36000) return false;
    speed_deg_per_sec_ = packet_[2] | (packet_[3] << 8);
    ++valid_packet_count_;

    LidarPoint points[LDSTL26_POINTS_PER_PACKET];
    uint8_t count = ParsePacket(packet_, points);
    bool completed = false;

    for (uint8_t i = 0; i < count; i++) {
        completed = scan_.Add(points[i], 180.0f, out_scan, out_count) || completed;
    }

    return completed;
}

uint8_t Ldstl26Lidar::ParsePacket(const uint8_t* b, LidarPoint* points) {
    uint16_t start = b[4] | (b[5] << 8);
    uint16_t end = b[42] | (b[43] << 8);
    uint16_t diff = (end + 36000 - start) % 36000;
    float step = diff / 1100.0f;

    for (int i = 0; i < LDSTL26_POINTS_PER_PACKET; i++) {
        int idx = 6 + i * 3;
        uint16_t distance = b[idx] | (b[idx + 1] << 8);
        float angle = start / 100.0f + step * i;

        if (angle >= 360.0f) angle -= 360.0f;

        points[i].angle = angle;
        points[i].distance = distance;
    }

    return LDSTL26_POINTS_PER_PACKET;
}

uint8_t Ldstl26Lidar::CRC8(const uint8_t* data, uint16_t len) {
    uint8_t crc = 0;

    while (len--) {
        crc ^= *data++;
        for (int i = 0; i < 8; i++)
            crc = (crc & 0x80) ? (crc << 1) ^ 0x4D : crc << 1;
    }

    return crc;
}
