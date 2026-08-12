#pragma once

#include <stddef.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "msg/pid_msg.h"

enum class WifiCommMode : uint8_t {
    kMavlinkUdp = 0,
    kMicroRos = 1,
    kMavlinkUart = 2,
};

struct MavlinkStatustextInfo {
    bool valid;
    uint8_t severity;
    uint32_t last_update_ms;
    char device_name[32];
    char ip[16];
    char text[51];
};

bool wifi_comm_mode_is_valid(WifiCommMode mode);
WifiCommMode wifi_comm_mode_next(WifiCommMode mode);
const char *wifi_comm_mode_to_runtime_value(WifiCommMode mode);
const char *wifi_comm_mode_to_display_name(WifiCommMode mode);

// ================= 全局标志位 =================
extern volatile bool g_emergency_stop;
extern volatile bool g_motion_busy;
extern volatile uint32_t g_lidar_scan_sequence;
extern volatile WifiCommMode g_wifi_comm_mode;
extern char g_microros_agent_ip[16];
extern uint16_t g_microros_agent_port;
extern char g_device_name[32];
extern MavlinkStatustextInfo g_mavlink_statustext;

// ================= 消息队列句柄 =================
extern QueueHandle_t q_imu_state;
extern QueueHandle_t q_motion_state;
extern QueueHandle_t q_ultrasonic_state;
extern QueueHandle_t q_lidar_state;   
extern QueueHandle_t q_gamepad_state;
extern QueueHandle_t q_temperature_state;
extern QueueHandle_t q_battery_state;


extern QueueHandle_t q_motion_cmd;
extern QueueHandle_t q_servo_cmd;
extern QueueHandle_t q_speedpid_cmd;
extern QueueHandle_t q_postionpid_cmd;

extern PidMsg g_speed_pid_state;
extern PidMsg g_position_pid_state;

// ================= 任务入口函数声明 =================
void motion_task(void *p);
void imu_task(void *p);
void ultrasonic_task(void *p);
void battery_task(void *p);
void peripheral_task(void *p);
void mavlink_udp_task(void *pvParameters);
void mavlink_uart_task(void *pvParameters);
void lidar_task(void *p);
void wifi_provision_task(void *pvParameters);
void espnow_task(void *p); // <--- 新增 ESP-NOW 任务声明
void gamepad_i2c_task(void *p);
void microros_task(void *p);
