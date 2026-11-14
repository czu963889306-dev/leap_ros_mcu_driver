#pragma once
#include <stdint.h>
using rmw_ret_t = int;
constexpr rmw_ret_t RMW_RET_OK = 0;
constexpr rmw_ret_t RMW_RET_ERROR = 1;
rmw_ret_t rmw_uros_sync_session(int timeout_ms);
bool rmw_uros_epoch_synchronized();
int64_t rmw_uros_epoch_millis();
