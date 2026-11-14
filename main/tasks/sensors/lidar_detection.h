#pragma once

#include <stdint.h>

enum class LidarModel { kUnknown, kStl26, kCamsense };

// Time and packet counts come from the task so probing can be tested on a host.
class LidarDetection {
public:
    LidarDetection(uint32_t probe_ms, uint32_t disconnect_ms, uint32_t min_packets)
        : probe_ms_(probe_ms), disconnect_ms_(disconnect_ms), min_packets_(min_packets) {}

    void Begin(uint32_t now_ms) {
        probe_ = LidarModel::kStl26;
        detected_ = LidarModel::kUnknown;
        probe_start_ms_ = last_packet_ms_ = now_ms;
        last_packet_count_ = 0;
    }

    // True means switch UART baud rate and reset both parsers.
    bool Update(uint32_t now_ms, uint32_t valid_packet_count) {
        if (valid_packet_count != last_packet_count_) {
            last_packet_ms_ = now_ms;
            last_packet_count_ = valid_packet_count;
        }
        if (detected_ == LidarModel::kUnknown && valid_packet_count >= min_packets_) {
            detected_ = probe_;
        }
        const bool expired = detected_ == LidarModel::kUnknown
            ? now_ms - probe_start_ms_ >= probe_ms_
            : now_ms - last_packet_ms_ >= disconnect_ms_;
        if (!expired) {
            return false;
        }
        probe_ = probe_ == LidarModel::kStl26 ? LidarModel::kCamsense : LidarModel::kStl26;
        detected_ = LidarModel::kUnknown;
        probe_start_ms_ = last_packet_ms_ = now_ms;
        last_packet_count_ = 0;
        return true;
    }

    LidarModel ProbeModel() const { return probe_; }
    LidarModel DetectedModel() const { return detected_; }

private:
    const uint32_t probe_ms_;
    const uint32_t disconnect_ms_;
    const uint32_t min_packets_;
    uint32_t probe_start_ms_ = 0;
    uint32_t last_packet_ms_ = 0;
    uint32_t last_packet_count_ = 0;
    LidarModel probe_ = LidarModel::kStl26;
    LidarModel detected_ = LidarModel::kUnknown;
};
