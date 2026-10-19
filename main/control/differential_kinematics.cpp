#include "differential_kinematics.h"

namespace motion_cfg = leap_config::motion;

void DifferentialKinematics::Inverse(float linear_x, float, float angular_z,
                                     float wheel_mms[motion_cfg::kWheelCount]) const {
  if (wheel_mms == nullptr) return;
  wheel_mms[0] = linear_x - angular_z * motion_cfg::kHalfTrackMm;
  wheel_mms[1] = linear_x + angular_z * motion_cfg::kHalfTrackMm;
}

void DifferentialKinematics::Forward(const float wheel_mms[motion_cfg::kWheelCount],
                                     float* linear_x, float* linear_y, float* angular_z) const {
  if (!wheel_mms || !linear_x || !linear_y || !angular_z) return;
  *linear_x = (wheel_mms[0] + wheel_mms[1]) / 2.0f;
  *linear_y = 0.0f;
  *angular_z = (-wheel_mms[0] + wheel_mms[1]) / (2.0f * motion_cfg::kHalfTrackMm);
}
