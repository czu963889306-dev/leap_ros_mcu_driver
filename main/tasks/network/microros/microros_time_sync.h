#pragma once

#include <stdint.h>

namespace microros {

// Call only from the ROS task, along with the other session operations.
void reset_time_sync();
void update_time_sync(int timeout_ms);
// Returns false before sync, after expiry, or while a backward correction catches up.
bool get_synced_stamp_ms(int64_t &stamp_ms);

}  // namespace microros
