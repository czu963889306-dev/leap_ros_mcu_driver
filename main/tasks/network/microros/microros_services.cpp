#include "microros_internal.h"

namespace microros {

static void set_speed_pid_response(
    leap_interfaces__srv__SetSpeedPid_Response *res,
    bool success,
    const PidMsg &pid_msg) {
    if (res == nullptr) {
        return;
    }
    res->success = success;
    res->kp = pid_msg.kp;
    res->ki = pid_msg.ki;
    res->kd = pid_msg.kd;
}

static void get_speed_pid_response(
    leap_interfaces__srv__GetSpeedPid_Response *res,
    bool success,
    const PidMsg &pid_msg) {
    if (res == nullptr) {
        return;
    }
    res->success = success;
    res->kp = pid_msg.kp;
    res->ki = pid_msg.ki;
    res->kd = pid_msg.kd;
}

void handle_set_speed_pid_service(const void *req, void *res) {
    auto *request = static_cast<const leap_interfaces__srv__SetSpeedPid_Request *>(req);
    auto *response = static_cast<leap_interfaces__srv__SetSpeedPid_Response *>(res);
    if (request == nullptr || response == nullptr || system_globals().queues.speedpid_cmd == nullptr ||
        !isfinite(request->kp) || !isfinite(request->ki) || !isfinite(request->kd)) {
        set_speed_pid_response(response, false, system_globals().control.speed_pid);
        return;
    }

    PidMsg pid_msg = {};
    pid_msg.kp = request->kp;
    pid_msg.ki = request->ki;
    pid_msg.kd = request->kd;
    esp_err_t save_err = pid_save_speed_config(&pid_msg);
    if (save_err != ESP_OK) {
        ESP_LOGE(kTag, "Failed to save speed PID config: %s", esp_err_to_name(save_err));
        set_speed_pid_response(response, false, system_globals().control.speed_pid);
        return;
    }

    system_globals().control.speed_pid = pid_msg;
    xQueueOverwrite(system_globals().queues.speedpid_cmd, &pid_msg);
    set_speed_pid_response(response, true, pid_msg);
    ESP_LOGI(kTag, "Speed PID service set and saved: kp=%.3f, ki=%.3f, kd=%.3f",
             pid_msg.kp, pid_msg.ki, pid_msg.kd);
}

void handle_get_speed_pid_service(const void *, void *res) {
    auto *response = static_cast<leap_interfaces__srv__GetSpeedPid_Response *>(res);
    get_speed_pid_response(response, true, system_globals().control.speed_pid);
}

void spin_pid_services() {
    if (s_service_executor_initialized) {
        MICROROS_RCSOFTCHECK(rclc_executor_spin_some(&s_service_executor, RCL_MS_TO_NS(0)));
    }
}

}  // namespace microros
