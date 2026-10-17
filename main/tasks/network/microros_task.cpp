#include "system_globals.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"
#include "msg/battery_msg.h"
#include "msg/imu_msg.h"
#include "msg/lidar_msg.h"
#include "msg/motion_msg.h"
#include "msg/ultrasonic_msg.h"
#include "pid_config.h"
#include "wifi_app.h"

#include "geometry_msgs/msg/twist.h"
#include "leap_interfaces/srv/get_speed_pid.h"
#include "leap_interfaces/srv/set_speed_pid.h"
#include "nav_msgs/msg/odometry.h"
#include "rcl/rcl.h"
#include "rcl/node_options.h"
#include "rcl/time.h"
#include "rcl/timer.h"
#include "rcl/wait.h"
#include "rclc/executor.h"
#include "rmw/qos_profiles.h"
#include "rmw_microros/custom_transport.h"
#include "rmw_microros/ping.h"
#include "rmw_microros/rmw_microros.h"
#include "rmw_microros/time_sync.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "rosidl_runtime_c/string_functions.h"
#include "sensor_msgs/msg/battery_state.h"
#include "sensor_msgs/msg/imu.h"
#include "sensor_msgs/msg/laser_scan.h"
#include "sensor_msgs/msg/range.h"
#include "std_msgs/msg/string.h"
#include "uxr/client/profile/transport/custom/custom_transport.h"

static const char *TAG = "MICROROS";
static constexpr size_t kLaserScanPointCount = 360;
static constexpr double kDegToRad = 0.017453292519943295;
static constexpr double kGravity = 9.80665;
static constexpr uart_port_t kMicroRosUartPort = UART_NUM_0;
static constexpr gpio_num_t kMicroRosUartTxPin = GPIO_NUM_43;
static constexpr gpio_num_t kMicroRosUartRxPin = GPIO_NUM_44;
static constexpr int kMicroRosUartBaudRate = 921600;
static constexpr size_t kMicroRosUartRxBufferSize = 4096;
static constexpr size_t kMicroRosUartTxBufferSize = 8192;
static constexpr int kMicroRosUartReadMaxWaitMs = 20;
static constexpr uint32_t kMicroRosUartStartupDelayMs = 5000;
static constexpr int kTimeSyncTimeoutMs = 1000;
static constexpr size_t kHostInfoTextCapacity = 96;
static constexpr size_t kWifiConfigTextCapacity = 256;
static constexpr uint32_t kWifiConfigPublishTicks = 50;

#ifndef CONFIG_MICRO_ROS_LOCAL_PORT
#define CONFIG_MICRO_ROS_LOCAL_PORT "8888"
#endif

struct UdpTransportContext {
    int fd;
    sockaddr_in remote;
    uint16_t local_port;
};

struct UartTransportContext {
    uart_port_t port;
};

static UdpTransportContext s_udp_ctx = {};
static UartTransportContext s_uart_ctx = {};
static bool s_uart_transport_initialized = false;
static geometry_msgs__msg__Twist s_cmd_vel_msg = {};
static nav_msgs__msg__Odometry s_odom_msg = {};
static sensor_msgs__msg__Imu s_imu_msg = {};
static sensor_msgs__msg__LaserScan s_scan_msg = {};
static sensor_msgs__msg__BatteryState s_battery_msg = {};
static sensor_msgs__msg__Range s_ultrasonic_msg = {};
static std_msgs__msg__String s_host_info_msg = {};
static std_msgs__msg__String s_wifi_config_msg = {};
static rcl_publisher_t s_odom_publisher = {};
static rcl_publisher_t s_imu_publisher = {};
static rcl_publisher_t s_scan_publisher = {};
static rcl_publisher_t s_battery_publisher = {};
static rcl_publisher_t s_ultrasonic_publisher = {};
static rcl_publisher_t s_wifi_config_publisher = {};
static rcl_subscription_t s_cmd_vel_subscriber = {};
static rcl_subscription_t s_host_info_subscriber = {};
static rcl_service_t s_set_speed_pid_service = {};
static rcl_service_t s_get_speed_pid_service = {};
static rclc_executor_t s_service_executor = {};
static leap_interfaces__srv__SetSpeedPid_Request s_set_speed_pid_req = {};
static leap_interfaces__srv__SetSpeedPid_Response s_set_speed_pid_res = {};
static leap_interfaces__srv__GetSpeedPid_Request s_get_speed_pid_req = {};
static leap_interfaces__srv__GetSpeedPid_Response s_get_speed_pid_res = {};
static rcl_init_options_t s_init_options = {};
static rcl_context_t s_context = {};
static rcl_allocator_t s_allocator = {};
static rcl_node_t s_node = {};
static rcl_timer_t s_publish_timer = {};
static rcl_wait_set_t s_wait_set = {};
static rcl_clock_t s_clock = {};
static bool s_ros_created = false;
static bool s_strings_initialized = false;
static bool s_scan_ranges_initialized = false;
static bool s_init_options_initialized = false;
static bool s_context_initialized = false;
static bool s_node_initialized = false;
static bool s_odom_publisher_initialized = false;
static bool s_imu_publisher_initialized = false;
static bool s_scan_publisher_initialized = false;
static bool s_battery_msg_initialized = false;
static bool s_battery_publisher_initialized = false;
static bool s_ultrasonic_publisher_initialized = false;
static bool s_wifi_config_publisher_initialized = false;
static bool s_cmd_vel_subscriber_initialized = false;
static bool s_host_info_subscriber_initialized = false;
static bool s_set_speed_pid_service_initialized = false;
static bool s_get_speed_pid_service_initialized = false;
static bool s_service_executor_initialized = false;
static bool s_clock_initialized = false;
static bool s_timer_initialized = false;
static bool s_wait_set_initialized = false;
static uint32_t s_publish_tick = 0;
static char s_host_info_data[kHostInfoTextCapacity] = {};
static char s_wifi_config_data[kWifiConfigTextCapacity] = {};
static char s_last_wifi_config_ssid[33] = {};

#define RCCHECK(fn) do { \
    rcl_ret_t rc = (fn); \
    if (rc != RCL_RET_OK) { \
        ESP_LOGW(TAG, "rcl status line %d: %d", __LINE__, static_cast<int>(rc)); \
        return false; \
    } \
} while (0)

#define RCSOFTCHECK(fn) do { \
    rcl_ret_t rc = (fn); \
    if (rc != RCL_RET_OK) { \
        ESP_LOGW(TAG, "rcl status line %d: %d", __LINE__, static_cast<int>(rc)); \
    } \
} while (0)

extern "C" bool transport_open_udp(uxrCustomTransport *transport) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    ctx->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (ctx->fd < 0) {
        return false;
    }

    sockaddr_in local = {};
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(ctx->local_port);
    bind(ctx->fd, reinterpret_cast<sockaddr *>(&local), sizeof(local));
    return true;
}

extern "C" bool transport_close_udp(uxrCustomTransport *transport) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    if (ctx->fd >= 0) {
        close(ctx->fd);
        ctx->fd = -1;
    }
    return true;
}

extern "C" size_t transport_write_udp(
    uxrCustomTransport *transport,
    const uint8_t *buf,
    size_t len,
    uint8_t *) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    const int sent = sendto(
        ctx->fd,
        buf,
        len,
        0,
        reinterpret_cast<sockaddr *>(&ctx->remote),
        sizeof(ctx->remote));
    return sent > 0 ? static_cast<size_t>(sent) : 0;
}

extern "C" size_t transport_read_udp(
    uxrCustomTransport *transport,
    uint8_t *buf,
    size_t len,
    int timeout,
    uint8_t *) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(ctx->fd, &readfds);

    timeval tv = {};
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
    const int ret = select(ctx->fd + 1, &readfds, nullptr, nullptr, &tv);
    if (ret <= 0) {
        return 0;
    }

    const int received = recv(ctx->fd, buf, len, 0);
    return received > 0 ? static_cast<size_t>(received) : 0;
}

static bool ensure_uart_driver_initialized(UartTransportContext *ctx) {
    if (ctx == nullptr) {
        return false;
    }

    if (s_uart_transport_initialized && uart_is_driver_installed(ctx->port)) {
        return true;
    }

    const uart_config_t uart_config = {
        .baud_rate = kMicroRosUartBaudRate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = {},
    };

    const bool driver_already_installed = uart_is_driver_installed(ctx->port);
    esp_err_t err = ESP_OK;
    if (!driver_already_installed) {
        err = uart_driver_install(
            ctx->port,
            kMicroRosUartRxBufferSize,
            kMicroRosUartTxBufferSize,
            0,
            nullptr,
            0);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "failed to install UART%d driver: %s",
                     static_cast<int>(ctx->port), esp_err_to_name(err));
            return false;
        }
    }

    err = uart_param_config(ctx->port, &uart_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "failed to configure UART%d: %s",
                 static_cast<int>(ctx->port), esp_err_to_name(err));
        if (!driver_already_installed) {
            uart_driver_delete(ctx->port);
        }
        return false;
    }

    err = uart_set_pin(
        ctx->port,
        kMicroRosUartTxPin,
        kMicroRosUartRxPin,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "failed to set UART%d pins: %s",
                 static_cast<int>(ctx->port), esp_err_to_name(err));
        if (!driver_already_installed) {
            uart_driver_delete(ctx->port);
        }
        return false;
    }

    uart_flush_input(ctx->port);
    s_uart_transport_initialized = true;
    return true;
}

static bool transport_open_uart(uxrCustomTransport *transport) {
    if (transport == nullptr) {
        return false;
    }
    return ensure_uart_driver_initialized(
        static_cast<UartTransportContext *>(transport->args));
}

static bool transport_close_uart(uxrCustomTransport *transport) {
    return transport != nullptr && transport->args != nullptr;
}

static size_t transport_write_uart(
    uxrCustomTransport *transport,
    const uint8_t *buf,
    size_t len,
    uint8_t *) {
    if (transport == nullptr || transport->args == nullptr || buf == nullptr || len == 0) {
        return 0;
    }

    auto *ctx = static_cast<UartTransportContext *>(transport->args);
    const int written = uart_write_bytes(
        ctx->port, reinterpret_cast<const char *>(buf), len);
    return written > 0 ? static_cast<size_t>(written) : 0;
}

static size_t transport_read_uart(
    uxrCustomTransport *transport,
    uint8_t *buf,
    size_t len,
    int timeout,
    uint8_t *) {
    if (transport == nullptr || transport->args == nullptr || buf == nullptr || len == 0) {
        return 0;
    }

    auto *ctx = static_cast<UartTransportContext *>(transport->args);
    const int wait_ms = timeout <= 0
        ? 0
        : (timeout > kMicroRosUartReadMaxWaitMs ? kMicroRosUartReadMaxWaitMs : timeout);
    const int received = uart_read_bytes(ctx->port, buf, len, pdMS_TO_TICKS(wait_ms));
    taskYIELD();
    return received > 0 ? static_cast<size_t>(received) : 0;
}

static void cleanup_result(rcl_ret_t ret) {
    if (ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "cleanup status: %d", static_cast<int>(ret));
    }
}

static void reset_ros_handles() {
    s_odom_publisher = rcl_get_zero_initialized_publisher();
    s_imu_publisher = rcl_get_zero_initialized_publisher();
    s_scan_publisher = rcl_get_zero_initialized_publisher();
    s_battery_publisher = rcl_get_zero_initialized_publisher();
    s_ultrasonic_publisher = rcl_get_zero_initialized_publisher();
    s_wifi_config_publisher = rcl_get_zero_initialized_publisher();
    s_cmd_vel_subscriber = rcl_get_zero_initialized_subscription();
    s_host_info_subscriber = rcl_get_zero_initialized_subscription();
    s_set_speed_pid_service = rcl_get_zero_initialized_service();
    s_get_speed_pid_service = rcl_get_zero_initialized_service();
    s_service_executor = rclc_executor_get_zero_initialized_executor();
    s_init_options = rcl_get_zero_initialized_init_options();
    s_context = rcl_get_zero_initialized_context();
    s_node = rcl_get_zero_initialized_node();
    s_publish_timer = rcl_get_zero_initialized_timer();
    s_wait_set = rcl_get_zero_initialized_wait_set();
    s_clock = {};
}

static void handle_cmd_vel(const geometry_msgs__msg__Twist *msg) {
    if (msg == nullptr || q_motion_cmd == nullptr) {
        return;
    }

    MotionMsg cmd = {};
    cmd.source = MOTION_SRC_MICROROS;
    cmd.control_mode = 0;
    cmd.target_vx = static_cast<float>(msg->linear.x * 1000.0);
    cmd.target_vy = static_cast<float>(msg->linear.y * 1000.0);
    cmd.target_wz = static_cast<float>(msg->angular.z);
    xQueueOverwrite(q_motion_cmd, &cmd);
    g_emergency_stop = false;
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

static void reset_host_info_state() {
    const TargetHostInfo empty = {};
    portENTER_CRITICAL(&g_target_host_info_lock);
    g_target_host_info = empty;
    portEXIT_CRITICAL(&g_target_host_info_lock);
}

static void handle_host_info(const std_msgs__msg__String *msg) {
    if (msg == nullptr || msg->data.data == nullptr || msg->data.size == 0) {
        return;
    }

    char text[kHostInfoTextCapacity] = {};
    const size_t text_len = msg->data.size < sizeof(text) - 1 ? msg->data.size : sizeof(text) - 1;
    memcpy(text, msg->data.data, text_len);
    text[text_len] = '\0';

    char hostname[sizeof(g_target_host_info.hostname)] = {};
    char hostip[sizeof(g_target_host_info.hostip)] = {};
    const bool has_hostname = extract_host_info_token(text, "hostname=", hostname, sizeof(hostname));
    bool has_hostip = extract_host_info_token(text, "hostip=", hostip, sizeof(hostip));
    if (!has_hostip) {
        has_hostip = extract_host_info_token(text, "ip=", hostip, sizeof(hostip));
    }
    if (!has_hostname || !has_hostip) {
        ESP_LOGW(TAG, "Invalid host_info text: %s", text);
        return;
    }

    TargetHostInfo updated = {};
    updated.valid = true;
    updated.last_update_ms = static_cast<uint32_t>(xTaskGetTickCount() * portTICK_PERIOD_MS);
    snprintf(updated.hostname, sizeof(updated.hostname), "%s", hostname);
    snprintf(updated.hostip, sizeof(updated.hostip), "%s", hostip);
    snprintf(updated.text, sizeof(updated.text), "%s", text);
    portENTER_CRITICAL(&g_target_host_info_lock);
    g_target_host_info = updated;
    portEXIT_CRITICAL(&g_target_host_info_lock);
    ESP_LOGI(TAG, "Host info received: hostname=%s hostip=%s text=%s",
             updated.hostname, updated.hostip, updated.text);
}

static bool append_json_char(char *out, size_t out_size, size_t *offset, char ch) {
    if (out == nullptr || offset == nullptr || *offset + 1 >= out_size) {
        return false;
    }
    out[(*offset)++] = ch;
    out[*offset] = '\0';
    return true;
}

static bool append_json_literal(char *out, size_t out_size, size_t *offset, const char *text) {
    if (text == nullptr) {
        return false;
    }
    while (*text != '\0') {
        if (!append_json_char(out, out_size, offset, *text++)) {
            return false;
        }
    }
    return true;
}

static bool append_json_escaped(char *out, size_t out_size, size_t *offset, const char *text) {
    if (text == nullptr) {
        return false;
    }
    while (*text != '\0') {
        const char ch = *text++;
        if ((ch == '"' || ch == '\\') && !append_json_char(out, out_size, offset, '\\')) {
            return false;
        }
        if (!append_json_char(out, out_size, offset, ch)) {
            return false;
        }
    }
    return true;
}

static bool build_wifi_config_payload(char *ssid_out, size_t ssid_out_size) {
    if (ssid_out == nullptr || ssid_out_size == 0) {
        return false;
    }

    char ssid[33] = {};
    char password[65] = {};
    if (wifi_load_sta_credentials_or_default(ssid, sizeof(ssid), password, sizeof(password)) != ESP_OK ||
        ssid[0] == '\0') {
        return false;
    }

    size_t offset = 0;
    s_wifi_config_data[0] = '\0';
    bool ok = append_json_literal(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, "{\"ssid\":\"");
    ok = ok && append_json_escaped(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, ssid);
    ok = ok && append_json_literal(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, "\",\"password\":\"");
    ok = ok && append_json_escaped(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, password);
    ok = ok && append_json_literal(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, "\"}");
    if (!ok) {
        s_wifi_config_data[0] = '\0';
        return false;
    }

    snprintf(ssid_out, ssid_out_size, "%s", ssid);
    return true;
}

static void publish_wifi_config() {
    if (!s_wifi_config_publisher_initialized || s_wifi_config_msg.data.data == nullptr) {
        return;
    }

    char ssid[33] = {};
    if (!build_wifi_config_payload(ssid, sizeof(ssid))) {
        return;
    }

    s_wifi_config_msg.data.size = strlen(s_wifi_config_data);
    s_wifi_config_msg.data.capacity = sizeof(s_wifi_config_data);
    RCSOFTCHECK(rcl_publish(&s_wifi_config_publisher, &s_wifi_config_msg, nullptr));
    if (strcmp(s_last_wifi_config_ssid, ssid) != 0) {
        snprintf(s_last_wifi_config_ssid, sizeof(s_last_wifi_config_ssid), "%s", ssid);
        ESP_LOGI(TAG, "Publishing wifi_config every 1s for SSID: %s", ssid);
    }
}

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

static void handle_set_speed_pid_service(const void *req, void *res) {
    auto *request = static_cast<const leap_interfaces__srv__SetSpeedPid_Request *>(req);
    auto *response = static_cast<leap_interfaces__srv__SetSpeedPid_Response *>(res);
    if (request == nullptr || response == nullptr || q_speedpid_cmd == nullptr ||
        !isfinite(request->kp) || !isfinite(request->ki) || !isfinite(request->kd)) {
        set_speed_pid_response(response, false, g_speed_pid_state);
        return;
    }

    PidMsg pid_msg = {};
    pid_msg.kp = request->kp;
    pid_msg.ki = request->ki;
    pid_msg.kd = request->kd;
    esp_err_t save_err = pid_save_speed_config(&pid_msg);
    if (save_err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to save speed PID config: %s", esp_err_to_name(save_err));
        set_speed_pid_response(response, false, g_speed_pid_state);
        return;
    }

    g_speed_pid_state = pid_msg;
    xQueueOverwrite(q_speedpid_cmd, &pid_msg);
    set_speed_pid_response(response, true, pid_msg);
    ESP_LOGI(TAG, "Speed PID service set and saved: kp=%.3f, ki=%.3f, kd=%.3f",
             pid_msg.kp, pid_msg.ki, pid_msg.kd);
}

static void handle_get_speed_pid_service(const void *, void *res) {
    auto *response = static_cast<leap_interfaces__srv__GetSpeedPid_Response *>(res);
    get_speed_pid_response(response, true, g_speed_pid_state);
}

static void spin_pid_services() {
    if (s_service_executor_initialized) {
        RCSOFTCHECK(rclc_executor_spin_some(&s_service_executor, RCL_MS_TO_NS(0)));
    }
}

static void set_stamp(std_msgs__msg__Header *header, int64_t stamp_ms) {
    header->stamp.sec = static_cast<int32_t>(stamp_ms / 1000);
    header->stamp.nanosec = static_cast<uint32_t>((stamp_ms % 1000) * 1000000);
}

static void publish_odom(int64_t stamp_ms) {
    MotionMsg motion = {};
    if (q_motion_state == nullptr || xQueuePeek(q_motion_state, &motion, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_odom_msg.header, stamp_ms);
    s_odom_msg.pose.pose.position.x = motion.x / 1000.0;
    s_odom_msg.pose.pose.position.y = motion.y / 1000.0;
    s_odom_msg.pose.pose.position.z = 0.0;
    s_odom_msg.pose.pose.orientation.w = motion.qw;
    s_odom_msg.pose.pose.orientation.x = motion.qx;
    s_odom_msg.pose.pose.orientation.y = motion.qy;
    s_odom_msg.pose.pose.orientation.z = motion.qz;
    s_odom_msg.twist.twist.linear.x = motion.vx / 1000.0;
    s_odom_msg.twist.twist.linear.y = motion.vy / 1000.0;
    s_odom_msg.twist.twist.angular.z = motion.wz;
    RCSOFTCHECK(rcl_publish(&s_odom_publisher, &s_odom_msg, nullptr));
}

static void publish_imu(int64_t stamp_ms) {
    ImuMsg imu = {};
    if (q_imu_state == nullptr || xQueuePeek(q_imu_state, &imu, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_imu_msg.header, stamp_ms);
    s_imu_msg.orientation.w = imu.qw;
    s_imu_msg.orientation.x = imu.qx;
    s_imu_msg.orientation.y = imu.qy;
    s_imu_msg.orientation.z = imu.qz;
    s_imu_msg.angular_velocity.x = imu.gyro_x * kDegToRad;
    s_imu_msg.angular_velocity.y = imu.gyro_y * kDegToRad;
    s_imu_msg.angular_velocity.z = imu.gyro_z * kDegToRad;
    s_imu_msg.linear_acceleration.x = imu.acc_x * kGravity;
    s_imu_msg.linear_acceleration.y = imu.acc_y * kGravity;
    s_imu_msg.linear_acceleration.z = imu.acc_z * kGravity;
    RCSOFTCHECK(rcl_publish(&s_imu_publisher, &s_imu_msg, nullptr));
}

static void publish_scan(int64_t stamp_ms) {
    LidarMsg lidar = {};
    if (q_lidar_state == nullptr || xQueuePeek(q_lidar_state, &lidar, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_scan_msg.header, stamp_ms);
    for (size_t i = 0; i < kLaserScanPointCount; ++i) {
        s_scan_msg.ranges.data[i] = lidar.distances[i] > 0
            ? static_cast<float>(lidar.distances[i]) / 1000.0f
            : 0.0f;
    }
    RCSOFTCHECK(rcl_publish(&s_scan_publisher, &s_scan_msg, nullptr));
}

static void publish_battery(int64_t stamp_ms) {
    BatteryMsg battery = {};
    if (q_battery_state == nullptr || xQueuePeek(q_battery_state, &battery, 0) != pdTRUE ||
        !battery.valid) {
        return;
    }

    set_stamp(&s_battery_msg.header, stamp_ms);
    s_battery_msg.voltage = battery.voltage_v;
    s_battery_msg.temperature = NAN;
    s_battery_msg.current = NAN;
    s_battery_msg.charge = NAN;
    s_battery_msg.capacity = NAN;
    s_battery_msg.design_capacity = NAN;
    s_battery_msg.percentage = static_cast<float>(battery.percentage) / 100.0f;
    s_battery_msg.power_supply_status =
        sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_DISCHARGING;
    s_battery_msg.power_supply_health =
        sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_GOOD;
    s_battery_msg.power_supply_technology =
        sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_LIPO;
    s_battery_msg.present = true;
    RCSOFTCHECK(rcl_publish(&s_battery_publisher, &s_battery_msg, nullptr));
}

static void publish_ultrasonic(int64_t stamp_ms) {
    UltrasonicMsg ultrasonic = {};
    if (q_ultrasonic_state == nullptr ||
        xQueuePeek(q_ultrasonic_state, &ultrasonic, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_ultrasonic_msg.header, stamp_ms);
    s_ultrasonic_msg.range = ultrasonic.distance_cm > 0.0f
        ? ultrasonic.distance_cm / 100.0f
        : NAN;
    RCSOFTCHECK(rcl_publish(&s_ultrasonic_publisher, &s_ultrasonic_msg, nullptr));
}

static void publish_state_timer(rcl_timer_t *timer, int64_t) {
    if (timer == nullptr ||
        (g_wifi_comm_mode != WifiCommMode::kMicroRos &&
         g_wifi_comm_mode != WifiCommMode::kMicroRosUart)) {
        return;
    }

    const int64_t stamp_ms = rmw_uros_epoch_millis();
    publish_odom(stamp_ms);
    publish_imu(stamp_ms);

    if ((++s_publish_tick % 5) == 0) {
        publish_scan(stamp_ms);
        publish_battery(stamp_ms);
        publish_ultrasonic(stamp_ms);
    }
    if ((s_publish_tick % kWifiConfigPublishTicks) == 0) {
        publish_wifi_config();
    }
}

static bool setup_udp_transport() {
    memset(&s_udp_ctx, 0, sizeof(s_udp_ctx));
    s_udp_ctx.fd = -1;
    s_udp_ctx.local_port = static_cast<uint16_t>(atoi(CONFIG_MICRO_ROS_LOCAL_PORT));
    s_udp_ctx.remote.sin_family = AF_INET;
    s_udp_ctx.remote.sin_port = htons(g_microros_agent_port);

    if (inet_pton(AF_INET, g_microros_agent_ip, &s_udp_ctx.remote.sin_addr.s_addr) != 1) {
        ESP_LOGE(TAG, "invalid micro-ROS agent IP: %s", g_microros_agent_ip);
        return false;
    }

    rmw_uros_set_custom_transport(
        false,
        &s_udp_ctx,
        transport_open_udp,
        transport_close_udp,
        transport_write_udp,
        transport_read_udp);
    return true;
}

static bool setup_uart_transport() {
    memset(&s_uart_ctx, 0, sizeof(s_uart_ctx));
    s_uart_ctx.port = kMicroRosUartPort;
    rmw_uros_set_custom_transport(
        true,
        &s_uart_ctx,
        transport_open_uart,
        transport_close_uart,
        transport_write_uart,
        transport_read_uart);
    return true;
}

static bool create_ros_entities() {
    s_publish_tick = 0;
    reset_ros_handles();
    reset_host_info_state();
    memset(s_host_info_data, 0, sizeof(s_host_info_data));
    s_host_info_msg.data.data = s_host_info_data;
    s_host_info_msg.data.size = 0;
    s_host_info_msg.data.capacity = sizeof(s_host_info_data);
    memset(s_wifi_config_data, 0, sizeof(s_wifi_config_data));
    s_wifi_config_msg.data.data = s_wifi_config_data;
    s_wifi_config_msg.data.size = 0;
    s_wifi_config_msg.data.capacity = sizeof(s_wifi_config_data);
    s_last_wifi_config_ssid[0] = '\0';

    rosidl_runtime_c__String__init(&s_odom_msg.header.frame_id);
    rosidl_runtime_c__String__init(&s_odom_msg.child_frame_id);
    rosidl_runtime_c__String__init(&s_imu_msg.header.frame_id);
    rosidl_runtime_c__String__init(&s_scan_msg.header.frame_id);
    rosidl_runtime_c__String__init(&s_ultrasonic_msg.header.frame_id);
    s_strings_initialized = true;

    (void)rosidl_runtime_c__String__assign(&s_odom_msg.header.frame_id, "odom");
    (void)rosidl_runtime_c__String__assign(&s_odom_msg.child_frame_id, "base_link");
    (void)rosidl_runtime_c__String__assign(&s_imu_msg.header.frame_id, "imu_link");
    (void)rosidl_runtime_c__String__assign(&s_scan_msg.header.frame_id, "laser_frame");
    (void)rosidl_runtime_c__String__assign(&s_ultrasonic_msg.header.frame_id, "ultrasonic_link");

    if (!rosidl_runtime_c__float32__Sequence__init(&s_scan_msg.ranges, kLaserScanPointCount)) {
        ESP_LOGE(TAG, "failed to allocate LaserScan ranges");
        return false;
    }
    s_scan_ranges_initialized = true;

    if (!sensor_msgs__msg__BatteryState__init(&s_battery_msg)) {
        ESP_LOGE(TAG, "failed to initialize BatteryState message");
        return false;
    }
    s_battery_msg_initialized = true;
    (void)rosidl_runtime_c__String__assign(&s_battery_msg.header.frame_id, "battery");
    (void)rosidl_runtime_c__String__assign(&s_battery_msg.location, "main");

    s_scan_msg.angle_min = 0.0f;
    s_scan_msg.angle_max = static_cast<float>((kLaserScanPointCount - 1) * kDegToRad);
    s_scan_msg.angle_increment = static_cast<float>(kDegToRad);
    s_scan_msg.time_increment = 0.0f;
    s_scan_msg.scan_time = 0.1f;
    s_scan_msg.range_min = 0.02f;
    s_scan_msg.range_max = 12.0f;

    s_ultrasonic_msg.radiation_type = sensor_msgs__msg__Range__ULTRASOUND;
    s_ultrasonic_msg.field_of_view = 0.26f;
    s_ultrasonic_msg.min_range = 0.02f;
    s_ultrasonic_msg.max_range = 4.0f;
    s_ultrasonic_msg.range = NAN;

    s_imu_msg.orientation_covariance[0] = -1.0;
    s_imu_msg.angular_velocity_covariance[0] = -1.0;
    s_imu_msg.linear_acceleration_covariance[0] = -1.0;

    s_allocator = rcl_get_default_allocator();
    s_init_options = rcl_get_zero_initialized_init_options();
    RCCHECK(rcl_init_options_init(&s_init_options, s_allocator));
    s_init_options_initialized = true;

    const rmw_ret_t ping_ret = rmw_uros_ping_agent(300, 3);
    if (ping_ret != RMW_RET_OK) {
        // ESP_LOGW(TAG, "micro-ROS agent unavailable: %s:%u",
        //          g_microros_agent_ip, static_cast<unsigned>(g_microros_agent_port));
        return false;
    }

    s_context = rcl_get_zero_initialized_context();
    RCCHECK(rcl_init(0, nullptr, &s_init_options, &s_context));
    s_context_initialized = true;

    if (!rmw_uros_epoch_synchronized()) {
        (void)rmw_uros_sync_session(kTimeSyncTimeoutMs);
    }

    s_node = rcl_get_zero_initialized_node();
    rcl_node_options_t node_options = rcl_node_get_default_options();
    node_options.enable_rosout = false;
    const rcl_ret_t node_ret = rcl_node_init(&s_node, "leap_ros", "", &s_context, &node_options);
    cleanup_result(rcl_node_options_fini(&node_options));
    if (node_ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "rcl status line %d: %d", __LINE__, static_cast<int>(node_ret));
        return false;
    }
    s_node_initialized = true;

    rcl_publisher_options_t state_pub_options = rcl_publisher_get_default_options();
    state_pub_options.qos = rmw_qos_profile_sensor_data;
    s_odom_publisher = rcl_get_zero_initialized_publisher();
    RCCHECK(rcl_publisher_init(
        &s_odom_publisher,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry),
        "odom",
        &state_pub_options));
    s_odom_publisher_initialized = true;

    s_imu_publisher = rcl_get_zero_initialized_publisher();
    RCCHECK(rcl_publisher_init(
        &s_imu_publisher,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu),
        "imu",
        &state_pub_options));
    s_imu_publisher_initialized = true;

    s_scan_publisher = rcl_get_zero_initialized_publisher();
    RCCHECK(rcl_publisher_init(
        &s_scan_publisher,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
        "scan",
        &state_pub_options));
    s_scan_publisher_initialized = true;

    s_battery_publisher = rcl_get_zero_initialized_publisher();
    RCCHECK(rcl_publisher_init(
        &s_battery_publisher,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, BatteryState),
        "battery_state",
        &state_pub_options));
    s_battery_publisher_initialized = true;

    s_ultrasonic_publisher = rcl_get_zero_initialized_publisher();
    RCCHECK(rcl_publisher_init(
        &s_ultrasonic_publisher,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Range),
        "ultrasonic",
        &state_pub_options));
    s_ultrasonic_publisher_initialized = true;

    rcl_publisher_options_t wifi_config_pub_options = rcl_publisher_get_default_options();
    wifi_config_pub_options.qos = rmw_qos_profile_sensor_data;
    s_wifi_config_publisher = rcl_get_zero_initialized_publisher();
    RCCHECK(rcl_publisher_init(
        &s_wifi_config_publisher,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "wifi_config",
        &wifi_config_pub_options));
    s_wifi_config_publisher_initialized = true;

    rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
    sub_options.qos = rmw_qos_profile_sensor_data;
    s_cmd_vel_subscriber = rcl_get_zero_initialized_subscription();
    RCCHECK(rcl_subscription_init(
        &s_cmd_vel_subscriber,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "cmd_vel",
        &sub_options));
    s_cmd_vel_subscriber_initialized = true;

    rcl_subscription_options_t host_info_sub_options = rcl_subscription_get_default_options();
    host_info_sub_options.qos = rmw_qos_profile_sensor_data;
    s_host_info_subscriber = rcl_get_zero_initialized_subscription();
    RCCHECK(rcl_subscription_init(
        &s_host_info_subscriber,
        &s_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "host_info",
        &host_info_sub_options));
    s_host_info_subscriber_initialized = true;

    rcl_service_options_t service_options = rcl_service_get_default_options();
    service_options.qos = rmw_qos_profile_services_default;
    RCCHECK(rcl_service_init(
        &s_set_speed_pid_service,
        &s_node,
        ROSIDL_GET_SRV_TYPE_SUPPORT(leap_interfaces, srv, SetSpeedPid),
        "set_speed_pid",
        &service_options));
    s_set_speed_pid_service_initialized = true;

    RCCHECK(rcl_service_init(
        &s_get_speed_pid_service,
        &s_node,
        ROSIDL_GET_SRV_TYPE_SUPPORT(leap_interfaces, srv, GetSpeedPid),
        "get_speed_pid",
        &service_options));
    s_get_speed_pid_service_initialized = true;

    RCCHECK(rclc_executor_init(&s_service_executor, &s_context, 2, &s_allocator));
    s_service_executor_initialized = true;
    RCCHECK(rclc_executor_add_service(
        &s_service_executor,
        &s_set_speed_pid_service,
        &s_set_speed_pid_req,
        &s_set_speed_pid_res,
        handle_set_speed_pid_service));
    RCCHECK(rclc_executor_add_service(
        &s_service_executor,
        &s_get_speed_pid_service,
        &s_get_speed_pid_req,
        &s_get_speed_pid_res,
        handle_get_speed_pid_service));

    s_clock = {};
    s_publish_timer = rcl_get_zero_initialized_timer();
    RCCHECK(rcl_steady_clock_init(&s_clock, &s_allocator));
    s_clock_initialized = true;
    RCCHECK(rcl_timer_init(
        &s_publish_timer,
        &s_clock,
        &s_context,
        RCL_MS_TO_NS(20),
        publish_state_timer,
        s_allocator));
    s_timer_initialized = true;

    s_wait_set = rcl_get_zero_initialized_wait_set();
    RCCHECK(rcl_wait_set_init(&s_wait_set, 2, 0, 1, 0, 0, 0, &s_context, s_allocator));
    s_wait_set_initialized = true;
    s_ros_created = true;
    return true;
}

static void destroy_ros_entities() {
    if (!s_ros_created &&
        !s_strings_initialized &&
        !s_scan_ranges_initialized &&
        !s_init_options_initialized &&
        !s_context_initialized) {
        return;
    }

    if (s_context_initialized) {
        rmw_context_t *rmw_context = rcl_context_get_rmw_context(&s_context);
        if (rmw_context) {
            (void)rmw_uros_set_context_entity_destroy_session_timeout(rmw_context, 0);
        }
    }

    if (s_wait_set_initialized) {
        cleanup_result(rcl_wait_set_fini(&s_wait_set));
        s_wait_set_initialized = false;
    }
    if (s_timer_initialized) {
        cleanup_result(rcl_timer_fini(&s_publish_timer));
        s_timer_initialized = false;
    }
    if (s_clock_initialized) {
        cleanup_result(rcl_clock_fini(&s_clock));
        s_clock_initialized = false;
    }
    if (s_ultrasonic_publisher_initialized) {
        cleanup_result(rcl_publisher_fini(&s_ultrasonic_publisher, &s_node));
        s_ultrasonic_publisher_initialized = false;
    }
    if (s_wifi_config_publisher_initialized) {
        cleanup_result(rcl_publisher_fini(&s_wifi_config_publisher, &s_node));
        s_wifi_config_publisher_initialized = false;
    }
    if (s_scan_publisher_initialized) {
        cleanup_result(rcl_publisher_fini(&s_scan_publisher, &s_node));
        s_scan_publisher_initialized = false;
    }
    if (s_battery_publisher_initialized) {
        cleanup_result(rcl_publisher_fini(&s_battery_publisher, &s_node));
        s_battery_publisher_initialized = false;
    }
    if (s_imu_publisher_initialized) {
        cleanup_result(rcl_publisher_fini(&s_imu_publisher, &s_node));
        s_imu_publisher_initialized = false;
    }
    if (s_odom_publisher_initialized) {
        cleanup_result(rcl_publisher_fini(&s_odom_publisher, &s_node));
        s_odom_publisher_initialized = false;
    }
    if (s_cmd_vel_subscriber_initialized) {
        cleanup_result(rcl_subscription_fini(&s_cmd_vel_subscriber, &s_node));
        s_cmd_vel_subscriber_initialized = false;
    }
    if (s_host_info_subscriber_initialized) {
        cleanup_result(rcl_subscription_fini(&s_host_info_subscriber, &s_node));
        s_host_info_subscriber_initialized = false;
    }
    if (s_service_executor_initialized) {
        cleanup_result(rclc_executor_fini(&s_service_executor));
        s_service_executor_initialized = false;
    }
    if (s_set_speed_pid_service_initialized) {
        cleanup_result(rcl_service_fini(&s_set_speed_pid_service, &s_node));
        s_set_speed_pid_service_initialized = false;
    }
    if (s_get_speed_pid_service_initialized) {
        cleanup_result(rcl_service_fini(&s_get_speed_pid_service, &s_node));
        s_get_speed_pid_service_initialized = false;
    }
    if (s_node_initialized) {
        cleanup_result(rcl_node_fini(&s_node));
        s_node_initialized = false;
    }
    if (s_context_initialized) {
        cleanup_result(rcl_shutdown(&s_context));
        cleanup_result(rcl_context_fini(&s_context));
        s_context_initialized = false;
    }
    if (s_init_options_initialized) {
        cleanup_result(rcl_init_options_fini(&s_init_options));
        s_init_options_initialized = false;
    }
    if (s_strings_initialized) {
        rosidl_runtime_c__String__fini(&s_odom_msg.header.frame_id);
        rosidl_runtime_c__String__fini(&s_odom_msg.child_frame_id);
        rosidl_runtime_c__String__fini(&s_imu_msg.header.frame_id);
        rosidl_runtime_c__String__fini(&s_scan_msg.header.frame_id);
        rosidl_runtime_c__String__fini(&s_ultrasonic_msg.header.frame_id);
        s_strings_initialized = false;
    }
    if (s_scan_ranges_initialized) {
        rosidl_runtime_c__float32__Sequence__fini(&s_scan_msg.ranges);
        s_scan_ranges_initialized = false;
    }
    if (s_battery_msg_initialized) {
        sensor_msgs__msg__BatteryState__fini(&s_battery_msg);
        s_battery_msg_initialized = false;
    }

    s_ros_created = false;
    reset_ros_handles();
}

static bool spin_once(int timeout_ms) {
    if (!s_wait_set_initialized) {
        return false;
    }

    rcl_ret_t ret = rcl_wait_set_clear(&s_wait_set);
    if (ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "rcl_wait_set_clear failed: %d", static_cast<int>(ret));
        return false;
    }
    ret = rcl_wait_set_add_subscription(&s_wait_set, &s_cmd_vel_subscriber, nullptr);
    if (ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "rcl_wait_set_add_subscription failed: %d", static_cast<int>(ret));
        return false;
    }
    ret = rcl_wait_set_add_subscription(&s_wait_set, &s_host_info_subscriber, nullptr);
    if (ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "rcl_wait_set_add_subscription failed: %d", static_cast<int>(ret));
        return false;
    }
    ret = rcl_wait_set_add_timer(&s_wait_set, &s_publish_timer, nullptr);
    if (ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "rcl_wait_set_add_timer failed: %d", static_cast<int>(ret));
        return false;
    }

    ret = rcl_wait(&s_wait_set, RCL_MS_TO_NS(timeout_ms));
    if (ret == RCL_RET_TIMEOUT) {
        spin_pid_services();
        return true;
    }
    if (ret != RCL_RET_OK) {
        ESP_LOGW(TAG, "rcl_wait failed: %d", static_cast<int>(ret));
        return false;
    }

    if (s_wait_set.subscriptions[0] != nullptr) {
        const rcl_ret_t take_ret = rcl_take(&s_cmd_vel_subscriber, &s_cmd_vel_msg, nullptr, nullptr);
        if (take_ret == RCL_RET_OK) {
            handle_cmd_vel(&s_cmd_vel_msg);
        } else if (take_ret != RCL_RET_SUBSCRIPTION_TAKE_FAILED) {
            ESP_LOGW(TAG, "rcl_take failed: %d", static_cast<int>(take_ret));
        }
    }

    if (s_wait_set.subscriptions[1] != nullptr) {
        const rcl_ret_t take_ret = rcl_take(&s_host_info_subscriber, &s_host_info_msg, nullptr, nullptr);
        if (take_ret == RCL_RET_OK) {
            handle_host_info(&s_host_info_msg);
        } else if (take_ret != RCL_RET_SUBSCRIPTION_TAKE_FAILED) {
            ESP_LOGW(TAG, "rcl_take host_info failed: %d", static_cast<int>(take_ret));
        }
    }

    if (s_wait_set.timers[0] != nullptr) {
        RCSOFTCHECK(rcl_timer_call(&s_publish_timer));
    }
    spin_pid_services();
    return true;
}

void microros_task(void *p) {
    (void)p;

    // UART0 is also the boot console. Leave it at the console settings long
    // enough for the Wi-Fi/IP startup logs to be emitted before micro-ROS
    // switches it to the XRCE-DDS UART transport (921600 baud).
    if (g_wifi_comm_mode == WifiCommMode::kMicroRosUart) {
        ESP_LOGI(TAG, "Delaying micro-ROS UART startup for %u ms",
                 static_cast<unsigned>(kMicroRosUartStartupDelayMs));
        vTaskDelay(pdMS_TO_TICKS(kMicroRosUartStartupDelayMs));
    }

    while (1) {
        const bool use_udp = g_wifi_comm_mode == WifiCommMode::kMicroRos;
        const bool use_uart = g_wifi_comm_mode == WifiCommMode::kMicroRosUart;
        if (use_udp || use_uart) {
            if (!s_ros_created) {
                const bool transport_ready = use_uart ? setup_uart_transport() : setup_udp_transport();
                if (transport_ready && create_ros_entities()) {
                    if (use_uart) {
                        ESP_LOGI(TAG, "micro-ROS UART active: UART%d TX=%d RX=%d baud=%d, pub=/odom,/imu,/scan,/battery_state,/ultrasonic,/wifi_config, sub=/cmd_vel,/host_info, srv=/set_speed_pid,/get_speed_pid",
                                 static_cast<int>(kMicroRosUartPort),
                                 static_cast<int>(kMicroRosUartTxPin),
                                 static_cast<int>(kMicroRosUartRxPin),
                                 kMicroRosUartBaudRate);
                    } else {
                        ESP_LOGI(TAG, "micro-ROS active: agent=%s:%u, pub=/odom,/imu,/scan,/battery_state,/ultrasonic,/wifi_config, sub=/cmd_vel,/host_info, srv=/set_speed_pid,/get_speed_pid",
                                 g_microros_agent_ip,
                                 static_cast<unsigned>(g_microros_agent_port));
                    }
                } else {
                    destroy_ros_entities();
                    vTaskDelay(pdMS_TO_TICKS(1000));
                    continue;
                }
            }
            if (!spin_once(20)) {
                ESP_LOGW(TAG, "micro-ROS transport stopped; recreating session");
                destroy_ros_entities();
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        } else {
            if (s_ros_created) {
                destroy_ros_entities();
                ESP_LOGI(TAG, "micro-ROS inactive");
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}
