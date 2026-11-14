#pragma once

#include <stdint.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "lidar_scan.h"

#define LDSTL26_PACKET_SIZE 47
#define LDSTL26_POINTS_PER_PACKET 12

class Ldstl26Lidar {
public:
    Ldstl26Lidar(uart_port_t uart_num, gpio_num_t tx_pin, gpio_num_t rx_pin,
                int baud_rate = 230400);
    void Init();
    void Reset();
    bool Poll(LidarPoint* out_scan, uint16_t* out_count);
    uint32_t ValidPacketCount() const { return valid_packet_count_; }

private:
    uart_port_t uart_num_;
    gpio_num_t tx_pin_, rx_pin_;
    int baud_rate_;
    uint8_t state_ = 0;
    uint8_t packet_idx_ = 0;
    uint8_t packet_[LDSTL26_PACKET_SIZE] = {};
    uint32_t valid_packet_count_ = 0;
    LidarScan scan_;

    bool ProcessByte(uint8_t data, LidarPoint* out_scan, uint16_t* out_count);
    uint8_t ParsePacket(const uint8_t* buffer, LidarPoint* points);
    uint8_t CRC8(const uint8_t* data, uint16_t len);
};
