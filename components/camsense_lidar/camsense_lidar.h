#pragma once

#include <stdint.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "lidar_scan.h"

#define MAX_LIDAR_PACKET_SIZE 128

class CamsenseLidar {
public:
    CamsenseLidar(uart_port_t uart_num, gpio_num_t tx_pin, gpio_num_t rx_pin,
                  int baud_rate = 115200);
    void Init();
    void Reset();
    bool Poll(LidarPoint* out_scan, uint16_t* out_count);
    uint32_t ValidPacketCount() const { return valid_packet_count_; }

private:
    uart_port_t uart_num_;
    gpio_num_t tx_pin_;
    gpio_num_t rx_pin_;
    int baud_rate_;
    int state_ = 0;
    uint8_t cInfo_ = 0;
    uint8_t N_ = 0;
    uint8_t payload_buffer_[MAX_LIDAR_PACKET_SIZE] = {};
    uint16_t payload_idx_ = 0;
    uint16_t expected_payload_len_ = 0;
    uint32_t valid_packet_count_ = 0;
    LidarScan scan_;

    bool ProcessByte(uint8_t rx_byte, LidarPoint* out_scan, uint16_t* out_count);
    bool PacketAnglesValid() const;
    uint8_t ParsePacket(const uint8_t* buffer, uint8_t cInfo, uint8_t N,
                        LidarPoint* packet_points);
};
