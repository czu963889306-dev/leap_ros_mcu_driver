#pragma once

#include "motion_config.h"

// Two-wheel differential drive; wheel order is left, right. Velocities are mm/s.
class DifferentialKinematics final {
 public:
  void Inverse(float linear_x, float linear_y, float angular_z,
               float wheel_mms[leap_config::motion::kWheelCount]) const;
  void Forward(const float wheel_mms[leap_config::motion::kWheelCount],
               float* linear_x, float* linear_y, float* angular_z) const;
};
