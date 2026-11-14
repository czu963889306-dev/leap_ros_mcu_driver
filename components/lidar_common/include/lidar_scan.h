#pragma once

#include <stdint.h>
#include <string.h>

#define MAX_LIDAR_POINTS_PER_SCAN 360
static constexpr float kLidarAngleOffsetDeg = 18.5f;

inline int LidarMirroredAngle(float angle) {
    const int rounded = static_cast<int>(angle + 0.5f) % MAX_LIDAR_POINTS_PER_SCAN;
    return (MAX_LIDAR_POINTS_PER_SCAN - rounded) % MAX_LIDAR_POINTS_PER_SCAN;
}

struct LidarPoint {
    float angle;
    float distance;
};

// Keep the nearest return in every angular bin, regardless of samples per turn.
class LidarScan {
public:
    void Reset() {
        memset(distances_, 0, sizeof(distances_));
        last_angle_ = 0.0f;
    }

    bool Add(const LidarPoint& point, float wrap_threshold,
             LidarPoint* out_scan, uint16_t* out_count) {
        const bool completed = point.angle < last_angle_ - wrap_threshold;
        if (completed) {
            uint16_t count = 0;
            for (int angle = 0; angle < MAX_LIDAR_POINTS_PER_SCAN; ++angle) {
                if (distances_[angle] != 0) {
                    if (out_scan != nullptr) {
                        out_scan[count] = {static_cast<float>(angle),
                                           static_cast<float>(distances_[angle])};
                    }
                    ++count;
                }
            }
            if (out_count != nullptr) {
                *out_count = count;
            }
            memset(distances_, 0, sizeof(distances_));
        }

        const int angle = static_cast<int>(point.angle + 0.5f) % MAX_LIDAR_POINTS_PER_SCAN;
        const uint16_t distance = static_cast<uint16_t>(point.distance);
        if (distance > 0 && (distances_[angle] == 0 || distance < distances_[angle])) {
            distances_[angle] = distance;
        }
        last_angle_ = point.angle;
        return completed;
    }

private:
    uint16_t distances_[MAX_LIDAR_POINTS_PER_SCAN] = {};
    float last_angle_ = 0.0f;
};
