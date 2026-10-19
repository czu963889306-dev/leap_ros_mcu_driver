#pragma once

#include <stddef.h>
#include <stdint.h>

namespace leap_config {
namespace ros {

static constexpr size_t kLaserScanPointCount = 360;
static constexpr double kDegToRad = 0.017453292519943295;
static constexpr double kGravity = 9.80665;
static constexpr int kTimeSyncTimeoutMs = 1000;
static constexpr size_t kHostInfoTextCapacity = 96;
static constexpr size_t kWifiConfigTextCapacity = 256;
static constexpr uint32_t kWifiConfigPublishTicks = 50;
static constexpr const char kNodeName[] = "leap_ros";
static constexpr const char kOdomFrame[] = "odom";
static constexpr const char kBaseFrame[] = "base_link";
static constexpr const char kImuFrame[] = "imu_link";
static constexpr const char kLaserFrame[] = "laser_frame";
static constexpr const char kBatteryFrame[] = "battery";
static constexpr const char kUltrasonicFrame[] = "ultrasonic_link";
static constexpr const char kOdomTopic[] = "odom";
static constexpr const char kImuTopic[] = "imu";
static constexpr const char kScanTopic[] = "scan";
static constexpr const char kBatteryTopic[] = "battery_state";
static constexpr const char kUltrasonicTopic[] = "ultrasonic";
static constexpr const char kWifiConfigTopic[] = "wifi_config";
static constexpr const char kCmdVelTopic[] = "cmd_vel";
static constexpr const char kHostInfoTopic[] = "host_info";
static constexpr const char kSetSpeedPidService[] = "set_speed_pid";
static constexpr const char kGetSpeedPidService[] = "get_speed_pid";
static constexpr uint32_t kPublishPeriodMs = 20;
static constexpr uint32_t kSlowPublishDivider = 5;
static constexpr float kScanTimeS = 0.1f;
static constexpr float kLaserRangeMinM = 0.02f;
static constexpr float kLaserRangeMaxM = 12.0f;
static constexpr float kUltrasonicFieldOfViewRad = 0.26f;
static constexpr float kUltrasonicRangeMinM = 0.02f;
static constexpr float kUltrasonicRangeMaxM = 4.0f;
static constexpr int kInitialAgentPingTimeoutMs = 300;
static constexpr uint8_t kInitialAgentPingAttempts = 3;

}  // namespace ros
}  // namespace leap_config
