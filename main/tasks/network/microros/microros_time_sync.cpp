#include "microros_time_sync.h"

#include "esp_log.h"
#include "esp_timer.h"
#include "rmw_microros/time_sync.h"
#include "ros_config.h"

namespace microros {
namespace {

namespace ros_cfg = leap_config::ros;
constexpr const char *kTag = "MICROROS_TIME";

bool s_sync_valid = false;
bool s_sync_attempted = false;
int64_t s_last_attempt_ms = 0;
int64_t s_last_success_ms = 0;

bool time_sync_valid(int64_t now_ms) {
    return s_sync_valid && rmw_uros_epoch_synchronized() &&
           now_ms - s_last_success_ms < ros_cfg::kTimeSyncMaxAgeMs;
}

}  // namespace

void reset_time_sync() {
    // Do not trust a library synchronization flag left over from another session.
    s_sync_valid = false;
    s_sync_attempted = false;
    s_last_attempt_ms = 0;
    s_last_success_ms = 0;
}

void update_time_sync(bool initial) {
    const int64_t now_ms = esp_timer_get_time() / 1000;
    const bool was_valid = time_sync_valid(now_ms);
    const int64_t interval_ms = was_valid ? ros_cfg::kTimeSyncIntervalMs
                                         : ros_cfg::kTimeSyncRetryIntervalMs;
    if (!initial && s_sync_attempted && now_ms - s_last_attempt_ms < interval_ms) {
        return;
    }

    const int timeout_ms = initial ? ros_cfg::kTimeSyncTimeoutMs
                                   : ros_cfg::kTimeSyncMaintenanceTimeoutMs;
    const rmw_ret_t ret = rmw_uros_sync_session(timeout_ms);
    // Measure from completion so a timed-out attempt cannot cause a busy retry loop.
    s_last_attempt_ms = esp_timer_get_time() / 1000;
    s_sync_attempted = true;
    s_sync_valid = ret == RMW_RET_OK && rmw_uros_epoch_synchronized() &&
                   rmw_uros_epoch_millis() > 0;
    if (s_sync_valid) {
        s_last_success_ms = s_last_attempt_ms;
        if (!was_valid) {
            ESP_LOGI(kTag, "Agent time synchronized; timestamped publishers enabled");
        }
    } else {
        ESP_LOGW(kTag, "Agent time sync failed (status=%d); timestamped publishers paused, retry in %lld ms",
                 static_cast<int>(ret),
                 static_cast<long long>(ros_cfg::kTimeSyncRetryIntervalMs));
    }
}

bool get_synchronized_time_ms(int64_t *stamp_ms) {
    if (stamp_ms == nullptr || !time_sync_valid(esp_timer_get_time() / 1000)) {
        return false;
    }
    const int64_t epoch_ms = rmw_uros_epoch_millis();
    if (epoch_ms <= 0) {
        s_sync_valid = false;
        return false;
    }
    *stamp_ms = epoch_ms;
    return true;
}

}  // namespace microros
