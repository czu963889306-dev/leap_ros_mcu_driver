#include <cassert>
#include <cstdio>
#include "microros_time_sync.h"
#include "ros_config.h"
#include "rmw_microros/time_sync.h"

namespace cfg = leap_config::ros;
constexpr int64_t kEpochMs = 1792553000000LL;
int64_t now_us, agent_offset_ms;
int calls, last_timeout;
rmw_ret_t result;
bool synchronized;

int64_t esp_timer_get_time() { return now_us; }
rmw_ret_t rmw_uros_sync_session(int timeout_ms) {
    ++calls;
    last_timeout = timeout_ms;
    return result;
}
bool rmw_uros_epoch_synchronized() { return synchronized; }
int64_t rmw_uros_epoch_millis() { return now_us / 1000 + agent_offset_ms; }

void reset() {
    now_us = 0;
    agent_offset_ms = kEpochMs;
    calls = 0;
    last_timeout = 0;
    result = RMW_RET_OK;
    synchronized = true;
    microros::reset_time_sync();
}
void at_ms(int64_t ms) { now_us = ms * 1000; }
void update() { microros::update_time_sync(cfg::kTimeSyncRuntimeTimeoutMs); }
int64_t stamp() {
    int64_t value = 0;
    assert(microros::get_synced_stamp_ms(value));
    return value;
}
void expect_paused() {
    int64_t value = -1;
    assert(!microros::get_synced_stamp_ms(value));
    assert(value == -1);
}

int main() {
    // First sync failure must not publish uptime or trust a stale library flag.
    reset();
    expect_paused();
    result = RMW_RET_ERROR;
    microros::update_time_sync(cfg::kTimeSyncTimeoutMs);
    assert(calls == 1 && last_timeout == 1000);
    expect_paused();
    at_ms(999); update(); assert(calls == 1);
    at_ms(1000); result = RMW_RET_OK; update();
    assert(calls == 2 && last_timeout == 50);
    assert(stamp() == kEpochMs + 1000);

    // Success/validity/epoch must all be checked before accepting a mapping.
    reset(); synchronized = false; update(); expect_paused();
    at_ms(1000); synchronized = true; agent_offset_ms = -1000;
    update(); expect_paused();
    at_ms(2000); agent_offset_ms = kEpochMs; update();
    assert(stamp() == kEpochMs + 2000);

    // Refresh even while the library still claims to be synchronized.
    reset(); update(); assert(stamp() == kEpochMs);
    at_ms(4999); update(); assert(calls == 1);
    at_ms(5000); agent_offset_ms += 700; update();
    assert(calls == 2 && stamp() == kEpochMs + 5700);

    // A 700 ms backward host step must never emit backwards/frozen stamps.
    reset(); update();
    at_ms(4999); const int64_t previous = stamp();
    at_ms(5000); agent_offset_ms -= 700; update(); expect_paused();
    at_ms(5699); expect_paused();
    at_ms(5700); assert(stamp() == previous + 1);

    // Failed/late exchanges cannot overwrite the last confirmed mapping.
    reset(); update();
    at_ms(5000); result = RMW_RET_ERROR; synchronized = false;
    agent_offset_ms += 900000; update();
    assert(stamp() == kEpochMs + 5000);
    at_ms(5999); update(); assert(calls == 2);
    assert(stamp() == kEpochMs + 5999);
    at_ms(6000); update(); assert(calls == 3);
    at_ms(29999); assert(stamp() == kEpochMs + 29999);
    at_ms(30000); expect_paused();
    result = RMW_RET_OK; synchronized = true; agent_offset_ms = kEpochMs;
    update(); assert(stamp() == kEpochMs + 30000);

    // Reconnection must require a new exchange, even with a stale true flag.
    microros::reset_time_sync(); expect_paused();
    const int previous_calls = calls;
    update(); assert(calls == previous_calls + 1);
    assert(stamp() == kEpochMs + 30000);

    // Scheduling and holdover use 64-bit monotonic time beyond 32-bit ms uptime.
    reset(); at_ms(5000000000LL); update();
    assert(stamp() == kEpochMs + 5000000000LL);
    at_ms(5000004999LL); update(); assert(calls == 1);
    at_ms(5000005000LL); update(); assert(calls == 2);
    assert(stamp() == kEpochMs + 5000005000LL);
    std::puts("Time sync tests passed: startup, retries, validation, periodic refresh, "
              "clock steps, holdover/expiry, reconnect, long uptime.");
}
