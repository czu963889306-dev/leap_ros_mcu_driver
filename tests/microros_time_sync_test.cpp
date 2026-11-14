#include <assert.h>
#include <stdio.h>

#include "microros_time_sync.h"
#include "rmw_microros/time_sync.h"
#include "ros_config.h"

namespace {
namespace cfg = leap_config::ros;
int64_t now_ms;
int64_t epoch_ms;
bool synchronized;
rmw_ret_t sync_result;
bool sync_flag_after_call;
int sync_duration_ms;
int sync_calls;
int last_timeout_ms;

void reset() {
    now_ms = 0;
    epoch_ms = 1700000000123;
    synchronized = false;
    sync_result = RMW_RET_OK;
    sync_flag_after_call = true;
    sync_duration_ms = 0;
    sync_calls = 0;
    last_timeout_ms = 0;
    microros::reset_time_sync();
}

bool can_publish() {
    int64_t stamp = -1;
    const bool valid = microros::get_synchronized_time_ms(&stamp);
    assert(stamp == (valid ? epoch_ms : -1));
    return valid;
}

void test_initial_sync_and_periodic_refresh() {
    reset();
    assert(!can_publish());
    microros::update_time_sync(true);
    assert(sync_calls == 1 && last_timeout_ms == cfg::kTimeSyncTimeoutMs);
    assert(can_publish());
    assert(!microros::get_synchronized_time_ms(nullptr));
    now_ms = cfg::kTimeSyncIntervalMs - 1;
    microros::update_time_sync();
    assert(sync_calls == 1);
    ++now_ms;
    microros::update_time_sync();
    assert(sync_calls == 2 && last_timeout_ms == cfg::kTimeSyncMaintenanceTimeoutMs);
    assert(can_publish());
}

void test_failed_initial_sync_retries_after_completion() {
    reset();
    sync_result = RMW_RET_ERROR;
    // The library flag alone must not override a failed return value.
    sync_flag_after_call = true;
    sync_duration_ms = cfg::kTimeSyncTimeoutMs;
    microros::update_time_sync(true);
    assert(!can_publish());
    microros::update_time_sync();
    assert(sync_calls == 1);
    now_ms += cfg::kTimeSyncRetryIntervalMs - 1;
    microros::update_time_sync();
    assert(sync_calls == 1);
    ++now_ms;
    sync_result = RMW_RET_OK;
    sync_duration_ms = 0;
    microros::update_time_sync();
    assert(sync_calls == 2);
    assert(last_timeout_ms == cfg::kTimeSyncMaintenanceTimeoutMs);
    assert(can_publish());
}

void test_periodic_failure_pauses_until_recovered() {
    reset();
    microros::update_time_sync(true);
    now_ms = cfg::kTimeSyncIntervalMs;
    sync_result = RMW_RET_ERROR;
    microros::update_time_sync();
    assert(!can_publish());
    now_ms += cfg::kTimeSyncRetryIntervalMs - 1;
    microros::update_time_sync();
    assert(sync_calls == 2);
    ++now_ms;
    sync_result = RMW_RET_OK;
    microros::update_time_sync();
    assert(sync_calls == 3 && can_publish());
}

void test_session_reset_requires_a_new_sync() {
    reset();
    microros::update_time_sync(true);
    assert(can_publish());
    microros::reset_time_sync();
    assert(synchronized && !can_publish());
    microros::update_time_sync();
    assert(sync_calls == 2 && can_publish());
    synchronized = false;
    assert(!can_publish());
    now_ms += cfg::kTimeSyncRetryIntervalMs;
    microros::update_time_sync();
    assert(sync_calls == 3 && can_publish());
}

void test_invalid_sync_flag_and_epoch() {
    reset();
    sync_flag_after_call = false;
    microros::update_time_sync(true);
    assert(!can_publish());
    now_ms += cfg::kTimeSyncRetryIntervalMs;
    sync_flag_after_call = true;
    epoch_ms = 0;
    microros::update_time_sync();
    assert(!can_publish());
    now_ms += cfg::kTimeSyncRetryIntervalMs;
    epoch_ms = 1700000000123;
    microros::update_time_sync();
    assert(can_publish());
    epoch_ms = -1;
    assert(!can_publish());
    epoch_ms = 1700000000123;
    assert(!can_publish());
    now_ms += cfg::kTimeSyncRetryIntervalMs;
    microros::update_time_sync();
    assert(can_publish());
}

void test_stale_sync_is_rejected() {
    reset();
    microros::update_time_sync(true);
    now_ms = cfg::kTimeSyncMaxAgeMs - 1;
    assert(can_publish());
    ++now_ms;
    assert(!can_publish());
    microros::update_time_sync();
    assert(sync_calls == 2 && can_publish());
    // Scheduling uses 64-bit uptime, including beyond a 32-bit millisecond wrap.
    now_ms += (int64_t{1} << 32);
    assert(!can_publish());
    microros::update_time_sync();
    assert(sync_calls == 3 && can_publish());
}
}  // namespace

int64_t esp_timer_get_time() { return now_ms * 1000; }
bool rmw_uros_epoch_synchronized() { return synchronized; }
int64_t rmw_uros_epoch_millis() { return epoch_ms; }
rmw_ret_t rmw_uros_sync_session(int timeout_ms) {
    ++sync_calls;
    last_timeout_ms = timeout_ms;
    now_ms += sync_duration_ms;
    synchronized = sync_flag_after_call;
    return sync_result;
}

int main() {
    test_initial_sync_and_periodic_refresh();
    test_failed_initial_sync_retries_after_completion();
    test_periodic_failure_pauses_until_recovered();
    test_session_reset_requires_a_new_sync();
    test_invalid_sync_flag_and_epoch();
    test_stale_sync_is_rejected();
    puts("6 time synchronization regression scenarios passed");
}
