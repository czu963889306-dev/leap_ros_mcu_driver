#pragma once

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

#include "network_config.h"
#include "ros_config.h"

namespace microros {

extern const char *const kTag;
namespace net_cfg = leap_config::network;
namespace ros_cfg = leap_config::ros;

struct UdpTransportContext {
    int fd;
    sockaddr_in remote;
    uint16_t local_port;
};

struct UartTransportContext {
    uart_port_t port;
};

extern UdpTransportContext s_udp_ctx;
extern UartTransportContext s_uart_ctx;
extern bool s_uart_transport_initialized;
extern geometry_msgs__msg__Twist s_cmd_vel_msg;
extern nav_msgs__msg__Odometry s_odom_msg;
extern sensor_msgs__msg__Imu s_imu_msg;
extern sensor_msgs__msg__LaserScan s_scan_msg;
extern sensor_msgs__msg__BatteryState s_battery_msg;
extern sensor_msgs__msg__Range s_ultrasonic_msg;
extern std_msgs__msg__String s_host_info_msg;
extern std_msgs__msg__String s_wifi_config_msg;
extern rcl_publisher_t s_odom_publisher;
extern rcl_publisher_t s_imu_publisher;
extern rcl_publisher_t s_scan_publisher;
extern rcl_publisher_t s_battery_publisher;
extern rcl_publisher_t s_ultrasonic_publisher;
extern rcl_publisher_t s_wifi_config_publisher;
extern rcl_subscription_t s_cmd_vel_subscriber;
extern rcl_subscription_t s_host_info_subscriber;
extern rcl_service_t s_set_speed_pid_service;
extern rcl_service_t s_get_speed_pid_service;
extern rclc_executor_t s_service_executor;
extern leap_interfaces__srv__SetSpeedPid_Request s_set_speed_pid_req;
extern leap_interfaces__srv__SetSpeedPid_Response s_set_speed_pid_res;
extern leap_interfaces__srv__GetSpeedPid_Request s_get_speed_pid_req;
extern leap_interfaces__srv__GetSpeedPid_Response s_get_speed_pid_res;
extern rcl_init_options_t s_init_options;
extern rcl_context_t s_context;
extern rcl_allocator_t s_allocator;
extern rcl_node_t s_node;
extern rcl_timer_t s_publish_timer;
extern rcl_wait_set_t s_wait_set;
extern rcl_clock_t s_clock;
extern bool s_ros_created;
extern bool s_strings_initialized;
extern bool s_scan_ranges_initialized;
extern bool s_init_options_initialized;
extern bool s_context_initialized;
extern bool s_node_initialized;
extern bool s_odom_publisher_initialized;
extern bool s_imu_publisher_initialized;
extern bool s_scan_publisher_initialized;
extern bool s_battery_msg_initialized;
extern bool s_battery_publisher_initialized;
extern bool s_ultrasonic_publisher_initialized;
extern bool s_wifi_config_publisher_initialized;
extern bool s_cmd_vel_subscriber_initialized;
extern bool s_host_info_subscriber_initialized;
extern bool s_set_speed_pid_service_initialized;
extern bool s_get_speed_pid_service_initialized;
extern bool s_service_executor_initialized;
extern bool s_clock_initialized;
extern bool s_timer_initialized;
extern bool s_wait_set_initialized;
extern uint32_t s_publish_tick;
extern char s_host_info_data[ros_cfg::kHostInfoTextCapacity];
extern char s_wifi_config_data[ros_cfg::kWifiConfigTextCapacity];
extern char s_last_wifi_config_ssid[33];


bool setup_udp_transport();
bool setup_uart_transport();
void cleanup_result(rcl_ret_t ret);
void reset_ros_handles();
void handle_cmd_vel(const geometry_msgs__msg__Twist *msg);
void reset_host_info_state();
void handle_host_info(const std_msgs__msg__String *msg);
void publish_state_timer(rcl_timer_t *timer, int64_t);
void handle_set_speed_pid_service(const void *req, void *res);
void handle_get_speed_pid_service(const void *, void *res);
void spin_pid_services();

}  // namespace microros

#define MICROROS_RCCHECK(fn) do { \
    rcl_ret_t rc = (fn); \
    if (rc != RCL_RET_OK) { \
        ESP_LOGW(microros::kTag, "rcl status line %d: %d", __LINE__, static_cast<int>(rc)); \
        return false; \
    } \
} while (0)

#define MICROROS_RCSOFTCHECK(fn) do { \
    rcl_ret_t rc = (fn); \
    if (rc != RCL_RET_OK) { \
        ESP_LOGW(microros::kTag, "rcl status line %d: %d", __LINE__, static_cast<int>(rc)); \
    } \
} while (0)
