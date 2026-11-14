#pragma once

#include <stdint.h>

namespace microros {

// All calls run on the micro-ROS task, alongside the session's other I/O.
void reset_time_sync();
void update_time_sync(bool initial = false);
bool get_synchronized_time_ms(int64_t *stamp_ms);

}  // namespace microros
