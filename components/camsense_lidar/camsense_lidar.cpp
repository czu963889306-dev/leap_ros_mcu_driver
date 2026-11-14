#include "camsense_lidar.h"
#include "esp_log.h"
#include <string.h>

static const char* TAG = "CamsenseLidar";

CamsenseLidar::CamsenseLidar(uart_port_t uart_num, gpio_num_t tx_pin, gpio_num_t rx_pin, int baud_rate)
    : uart_num_(uart_num),
      tx_pin_(tx_pin),
      rx_pin_(rx_pin),
      baud_rate_(baud_rate) {
}

void CamsenseLidar::Init() {
    uart_config_t uart_config = {};
    uart_config.baud_rate = baud_rate_;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity    = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.source_clk = UART_SCLK_DEFAULT;

    // 适当加大 RX 缓冲
    ESP_ERROR_CHECK(uart_driver_install(uart_num_, 2048, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num_, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num_, tx_pin_, rx_pin_, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_LOGI(TAG, "Lidar UART initialized on Port %d, Baud %d", uart_num_, baud_rate_);
}

void CamsenseLidar::Reset() {
    state_ = 0;
    cInfo_ = 0;
    N_ = 0;
    payload_idx_ = 0;
    expected_payload_len_ = 0;
    valid_packet_count_ = 0;
    scan_.Reset();
}

bool CamsenseLidar::PacketAnglesValid() const {
    const uint16_t first = payload_buffer_[2] | (payload_buffer_[3] << 8);
    const int last_index = 4 + N_ * cInfo_;
    const uint16_t last = payload_buffer_[last_index] | (payload_buffer_[last_index + 1] << 8);
    return first >= 0xA000 && first <= 0xFA00 && last >= 0xA000 && last <= 0xFA00;
}

bool CamsenseLidar::Poll(LidarPoint* out_scan, uint16_t* out_count) {
    size_t available = 0;
    uart_get_buffered_data_len(uart_num_, &available);

    if (available == 0) {
        return false;
    }

    // 限制单次最大读取量，确保不会霸占 CPU（留时间给系统喂狗）
    if (available > 512) {
        available = 512;
    }

    uint8_t rx_buf[512];
    int read_len = uart_read_bytes(uart_num_, rx_buf, available, 0);

    bool circle_completed = false;

    // 在内存中极速跑状态机
    for (int i = 0; i < read_len; i++) {
        if (ProcessByte(rx_buf[i], out_scan, out_count)) {
            circle_completed = true;
        }
    }

    return circle_completed;
}

bool CamsenseLidar::ProcessByte(uint8_t rx_byte, LidarPoint* out_scan, uint16_t* out_count) {
    bool circle_completed = false;

    if (state_ == 0) {
        if (rx_byte == 0x55) state_ = 1;
    } else if (state_ == 1) {
        if (rx_byte == 0xAA) state_ = 2;
        else if (rx_byte == 0x55) state_ = 1;
        else state_ = 0;
    } else if (state_ == 2) {
        cInfo_ = rx_byte;
        state_ = 3;
    } else if (state_ == 3) {
        N_ = rx_byte;
        expected_payload_len_ = N_ * cInfo_ + 8;

        // This decoder supports two-byte distance records, up to 60 per packet.
        if (expected_payload_len_ > MAX_LIDAR_PACKET_SIZE || cInfo_ != 2 || N_ > 60 || N_ == 0) {
            state_ = 0;
        } else {
            payload_idx_ = 0;
            state_ = 4;
        }
    } else if (state_ == 4) {
        payload_buffer_[payload_idx_++] = rx_byte;

        if (payload_idx_ >= expected_payload_len_) {
            if (PacketAnglesValid()) {
                ++valid_packet_count_;
                LidarPoint packet_points[60];
                const uint8_t valid_points = ParsePacket(payload_buffer_, cInfo_, N_, packet_points);
                for (uint8_t i = 0; i < valid_points; ++i) {
                    circle_completed = scan_.Add(packet_points[i], 100.0f, out_scan, out_count) || circle_completed;
                }
            }
            state_ = 0;
        }
    }

    return circle_completed;
}

uint8_t CamsenseLidar::ParsePacket(const uint8_t* buffer, uint8_t cInfo, uint8_t N,
                                  LidarPoint* packet_points) {
    const float first_angle = (buffer[3] - 0xA0 + buffer[2] / 256.0f) * 4.0f;
    const int last_index = 4 + N * cInfo;
    float last_angle = (buffer[last_index + 1] - 0xA0 + buffer[last_index] / 256.0f) * 4.0f;
    if (last_angle < first_angle) {
        last_angle += 360.0f;
    }
    const float step = N > 1 ? (last_angle - first_angle) / (N - 1) : 0.0f;

    for (uint8_t i = 0; i < N; ++i) {
        const int index = 4 + i * cInfo;
        const uint16_t distance = (buffer[index] | ((buffer[index + 1] & 0x3F) << 8));
        const bool valid = (buffer[index + 1] & 0x80) == 0;
        float angle = first_angle + step * i + kLidarAngleOffsetDeg;
        while (angle >= 360.0f) {
            angle -= 360.0f;
        }
        // Keep invalid points' angles so empty turns still complete normally.
        packet_points[i] = {angle, valid ? static_cast<float>(distance) : 0.0f};
    }
    return N;
}
