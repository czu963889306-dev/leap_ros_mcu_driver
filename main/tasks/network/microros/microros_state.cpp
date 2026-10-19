#include "microros_internal.h"

namespace microros {

const char *const kTag = "MICROROS";

UdpTransportContext s_udp_ctx = {};
UartTransportContext s_uart_ctx = {};
bool s_uart_transport_initialized = false;
geometry_msgs__msg__Twist s_cmd_vel_msg = {};
nav_msgs__msg__Odometry s_odom_msg = {};
sensor_msgs__msg__Imu s_imu_msg = {};
sensor_msgs__msg__LaserScan s_scan_msg = {};
sensor_msgs__msg__BatteryState s_battery_msg = {};
sensor_msgs__msg__Range s_ultrasonic_msg = {};
std_msgs__msg__String s_host_info_msg = {};
std_msgs__msg__String s_wifi_config_msg = {};
rcl_publisher_t s_odom_publisher = {};
rcl_publisher_t s_imu_publisher = {};
rcl_publisher_t s_scan_publisher = {};
rcl_publisher_t s_battery_publisher = {};
rcl_publisher_t s_ultrasonic_publisher = {};
rcl_publisher_t s_wifi_config_publisher = {};
rcl_subscription_t s_cmd_vel_subscriber = {};
rcl_subscription_t s_host_info_subscriber = {};
rcl_service_t s_set_speed_pid_service = {};
rcl_service_t s_get_speed_pid_service = {};
rclc_executor_t s_service_executor = {};
leap_interfaces__srv__SetSpeedPid_Request s_set_speed_pid_req = {};
leap_interfaces__srv__SetSpeedPid_Response s_set_speed_pid_res = {};
leap_interfaces__srv__GetSpeedPid_Request s_get_speed_pid_req = {};
leap_interfaces__srv__GetSpeedPid_Response s_get_speed_pid_res = {};
rcl_init_options_t s_init_options = {};
rcl_context_t s_context = {};
rcl_allocator_t s_allocator = {};
rcl_node_t s_node = {};
rcl_timer_t s_publish_timer = {};
rcl_wait_set_t s_wait_set = {};
rcl_clock_t s_clock = {};
bool s_ros_created = false;
bool s_strings_initialized = false;
bool s_scan_ranges_initialized = false;
bool s_init_options_initialized = false;
bool s_context_initialized = false;
bool s_node_initialized = false;
bool s_odom_publisher_initialized = false;
bool s_imu_publisher_initialized = false;
bool s_scan_publisher_initialized = false;
bool s_battery_msg_initialized = false;
bool s_battery_publisher_initialized = false;
bool s_ultrasonic_publisher_initialized = false;
bool s_wifi_config_publisher_initialized = false;
bool s_cmd_vel_subscriber_initialized = false;
bool s_host_info_subscriber_initialized = false;
bool s_set_speed_pid_service_initialized = false;
bool s_get_speed_pid_service_initialized = false;
bool s_service_executor_initialized = false;
bool s_clock_initialized = false;
bool s_timer_initialized = false;
bool s_wait_set_initialized = false;
uint32_t s_publish_tick = 0;
char s_host_info_data[ros_cfg::kHostInfoTextCapacity] = {};
char s_wifi_config_data[ros_cfg::kWifiConfigTextCapacity] = {};
char s_last_wifi_config_ssid[33] = {};

void cleanup_result(rcl_ret_t ret) {
    if (ret != RCL_RET_OK) {
        ESP_LOGW(kTag, "cleanup status: %d", static_cast<int>(ret));
    }
}

void reset_ros_handles() {
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

}  // namespace microros
