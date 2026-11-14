#include "microros_time_sync.h"

#include "esp_log.h"
#include "esp_timer.h"
#include "rmw_microros/time_sync.h"
#include "ros_config.h"

namespace microros {
namespace {

namespace cfg = leap_config::ros;
constexpr const char *kTag = "microros_time";
bool s_have_sync = false;
bool s_sync_failed = false;
bool s_stamp_paused = false;
int64_t s_next_sync_us = 0;
int64_t s_sync_us = 0;
int64_t s_epoch_ms = 0;
int64_t s_last_stamp_ms = 0;

}  // namespace

void reset_time_sync() {
    s_have_sync = false;
    s_sync_failed = false;
    s_stamp_paused = false;
    s_next_sync_us = 0;
    s_sync_us = 0;
    s_epoch_ms = 0;
    s_last_stamp_ms = 0;
}

void update_time_sync(int timeout_ms) {
    if (esp_timer_get_time() < s_next_sync_us) {
        return;
    }

    // Always request a fresh exchange: the library's synchronized flag does not
    // indicate whether the host clock has changed since the previous exchange.
    const rmw_ret_t ret = rmw_uros_sync_session(timeout_ms);
    const int64_t now_us = esp_timer_get_time();
    const int64_t epoch_ms = rmw_uros_epoch_millis();
    if (ret != RMW_RET_OK || !rmw_uros_epoch_synchronized() || epoch_ms <= 0) {
        s_next_sync_us = now_us + static_cast<int64_t>(cfg::kTimeSyncRetryIntervalMs) * 1000;
        if (!s_sync_failed) {
            ESP_LOGW(kTag, "Agent time sync failed; retrying every %u ms",
                     static_cast<unsigned>(cfg::kTimeSyncRetryIntervalMs));
        }
        s_sync_failed = true;
        return;
    }

    const int64_t correction_ms = s_have_sync
        ? epoch_ms - (s_epoch_ms + (now_us - s_sync_us) / 1000)
        : 0;
    if (!s_have_sync || s_sync_failed) {
        ESP_LOGI(kTag, "Agent time synchronized; refreshing every %u ms",
                 static_cast<unsigned>(cfg::kTimeSyncIntervalMs));
    }
    if (s_have_sync && (correction_ms > 100 || correction_ms < -100)) {
        ESP_LOGW(kTag, "Agent clock correction: %lld ms",
                 static_cast<long long>(correction_ms));
    }
    // Keep our last confirmed epoch anchored to the monotonic ESP timer. A
    // failed exchange (or a late reply) must not replace this usable mapping.
    s_have_sync = true;
    s_sync_failed = false;
    s_sync_us = now_us;
    s_epoch_ms = epoch_ms;
    s_next_sync_us = now_us + static_cast<int64_t>(cfg::kTimeSyncIntervalMs) * 1000;
}

bool get_synced_stamp_ms(int64_t &stamp_ms) {
    if (!s_have_sync) {
        return false;
    }
    const int64_t age_us = esp_timer_get_time() - s_sync_us;
    if (age_us >= static_cast<int64_t>(cfg::kTimeSyncMaxAgeMs) * 1000) {
        if (!s_stamp_paused) {
            ESP_LOGW(kTag, "Agent time sync expired; pausing stamped sensor data");
            s_stamp_paused = true;
        }
        return false;
    }

    const int64_t candidate_ms = s_epoch_ms + age_us / 1000;
    if (candidate_ms <= s_last_stamp_ms) {
        // Do not clamp to the old (future) stamp or send decreasing stamps to
        // EKF/TF after the host steps its clock backward. Wait for it to catch up.
        if (!s_stamp_paused) {
            ESP_LOGW(kTag, "Waiting for corrected clock to pass last sensor stamp");
            s_stamp_paused = true;
        }
        return false;
    }
    if (s_stamp_paused) {
        ESP_LOGI(kTag, "Resuming stamped sensor data");
        s_stamp_paused = false;
    }
    s_last_stamp_ms = candidate_ms;
    stamp_ms = candidate_ms;
    return true;
}

}  // namespace microros
