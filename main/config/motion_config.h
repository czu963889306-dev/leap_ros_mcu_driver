#pragma once

#include <stdint.h>

namespace leap_config {
namespace motion {

static constexpr int kWheelCount = 2;
static constexpr float kWheelDiameterMm = 65.0f;
static constexpr float kTrackWidthMm = 131.7f;
static constexpr float kHalfTrackMm = kTrackWidthMm / 2.0f;
static constexpr float kRpmToMmS = (3.14159265358979323846 * kWheelDiameterMm) / 60.0f;
static constexpr float kMmSToRpm = 1.0f / kRpmToMmS;
static constexpr float kPulsesPerWheelRev = 4680.0f;
static constexpr int kEncoderSigns[kWheelCount] = {-1, 1};
static constexpr float kDefaultSpeedKp = 1.0f;
static constexpr float kDefaultSpeedKi = 6.0f;
static constexpr float kDefaultSpeedKd = 0.0f;
static constexpr float kDefaultPositionKp = 2.1f;
static constexpr float kDefaultPositionKi = 0.0f;
static constexpr float kDefaultPositionKd = 0.5f;
static constexpr float kDefaultYawKp = 2.5f;
static constexpr float kDefaultYawKi = 0.0f;
static constexpr float kDefaultYawKd = 0.5f;
static constexpr float kMaxPwm = 255.0f;
static constexpr float kMotorPwmDeadband = 150.0f;
static constexpr float kVelocityFilterAlpha = 0.35f;
static constexpr float kMaxPositionVelocityMmS = 250.0f;
static constexpr float kMaxPositionYawRadS = 3.0f;
static constexpr int kRelativeTurnSettleMaxCycles = 5;
static constexpr float kRelativeTurnSettleVxMms = 10.0f;
static constexpr float kDefaultMaxAccelerationRpmS = 200.0f;
static constexpr uint32_t kControlLoopPeriodMs = 20;
static constexpr float kControlLoopDtS = kControlLoopPeriodMs / 1000.0f;

}  // namespace motion
}  // namespace leap_config
