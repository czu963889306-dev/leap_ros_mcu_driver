#include "microros_internal.h"

namespace microros {

void handle_cmd_vel(const geometry_msgs__msg__Twist *msg) {
    if (msg == nullptr || system_globals().queues.motion_cmd == nullptr) {
        return;
    }

    MotionMsg cmd = {};
    cmd.source = MOTION_SRC_MICROROS;
    cmd.control_mode = 0;
    cmd.target_vx = static_cast<float>(msg->linear.x * 1000.0);
    cmd.target_vy = static_cast<float>(msg->linear.y * 1000.0);
    cmd.target_wz = static_cast<float>(msg->angular.z);
    xQueueOverwrite(system_globals().queues.motion_cmd, &cmd);
    system_globals().flags.emergency_stop = false;
}

static void copy_host_info_field(char *out, size_t out_size, const char *start, size_t len) {
    if (out == nullptr || out_size == 0) {
        return;
    }
    const size_t copy_len = len < out_size - 1 ? len : out_size - 1;
    if (copy_len > 0 && start != nullptr) {
        memcpy(out, start, copy_len);
    }
    out[copy_len] = '\0';
}

static bool extract_host_info_token(const char *text, const char *key, char *out, size_t out_size) {
    if (text == nullptr || key == nullptr || out == nullptr || out_size == 0) {
        return false;
    }

    const char *start = strstr(text, key);
    if (start == nullptr) {
        out[0] = '\0';
        return false;
    }
    start += strlen(key);

    const char *end = start;
    while (*end != '\0' && *end != ' ' && *end != ',' && *end != ';') {
        ++end;
    }
    copy_host_info_field(out, out_size, start, static_cast<size_t>(end - start));
    return out[0] != '\0';
}

void reset_host_info_state() {
    const TargetHostInfo empty = {};
    portENTER_CRITICAL(&system_globals().target_host_info_lock);
    system_globals().runtime.target_host_info = empty;
    portEXIT_CRITICAL(&system_globals().target_host_info_lock);
}

void handle_host_info(const std_msgs__msg__String *msg) {
    if (msg == nullptr || msg->data.data == nullptr || msg->data.size == 0) {
        return;
    }

    char text[ros_cfg::kHostInfoTextCapacity] = {};
    const size_t text_len = msg->data.size < sizeof(text) - 1 ? msg->data.size : sizeof(text) - 1;
    memcpy(text, msg->data.data, text_len);
    text[text_len] = '\0';

    char hostname[sizeof(system_globals().runtime.target_host_info.hostname)] = {};
    char hostip[sizeof(system_globals().runtime.target_host_info.hostip)] = {};
    const bool has_hostname = extract_host_info_token(text, "hostname=", hostname, sizeof(hostname));
    bool has_hostip = extract_host_info_token(text, "hostip=", hostip, sizeof(hostip));
    if (!has_hostip) {
        has_hostip = extract_host_info_token(text, "ip=", hostip, sizeof(hostip));
    }
    if (!has_hostname || !has_hostip) {
        ESP_LOGW(kTag, "Invalid host_info text: %s", text);
        return;
    }

    TargetHostInfo updated = {};
    updated.valid = true;
    updated.last_update_ms = static_cast<uint32_t>(xTaskGetTickCount() * portTICK_PERIOD_MS);
    snprintf(updated.hostname, sizeof(updated.hostname), "%s", hostname);
    snprintf(updated.hostip, sizeof(updated.hostip), "%s", hostip);
    snprintf(updated.text, sizeof(updated.text), "%s", text);
    portENTER_CRITICAL(&system_globals().target_host_info_lock);
    system_globals().runtime.target_host_info = updated;
    portEXIT_CRITICAL(&system_globals().target_host_info_lock);
    ESP_LOGI(kTag, "Host info received: hostname=%s hostip=%s text=%s",
             updated.hostname, updated.hostip, updated.text);
}

}  // namespace microros
