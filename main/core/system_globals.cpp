#include "system_globals.h"

volatile bool g_emergency_stop = false;
volatile bool g_motion_busy = false;
volatile uint32_t g_lidar_scan_sequence = 0;
volatile WifiCommMode g_wifi_comm_mode = WifiCommMode::kMicroRos;
char g_microros_agent_ip[16] = "192.168.31.214";
uint16_t g_microros_agent_port = 8888;
char g_device_name[32] = "Maturo_UNKNOWN";
MavlinkStatustextInfo g_mavlink_statustext = {
    .valid = false,
    .severity = 0,
    .last_update_ms = 0,
    .device_name = {0},
    .ip = {0},
    .text = {0},
};

bool wifi_comm_mode_is_valid(WifiCommMode mode) {
    return mode == WifiCommMode::kMavlinkUdp ||
           mode == WifiCommMode::kMicroRos ||
           mode == WifiCommMode::kMavlinkUart;
}

WifiCommMode wifi_comm_mode_next(WifiCommMode mode) {
    switch (mode) {
    case WifiCommMode::kMicroRos:
        return WifiCommMode::kMavlinkUdp;
    case WifiCommMode::kMavlinkUdp:
        return WifiCommMode::kMavlinkUart;
    case WifiCommMode::kMavlinkUart:
    default:
        return WifiCommMode::kMicroRos;
    }
}

const char *wifi_comm_mode_to_runtime_value(WifiCommMode mode) {
    switch (mode) {
    case WifiCommMode::kMicroRos:
        return "micro_ros";
    case WifiCommMode::kMavlinkUdp:
        return "mavlink_udp";
    case WifiCommMode::kMavlinkUart:
        return "uart_mavlink";
    default:
        return "unknown";
    }
}

const char *wifi_comm_mode_to_display_name(WifiCommMode mode) {
    switch (mode) {
    case WifiCommMode::kMicroRos:
        return "micro-ROS";
    case WifiCommMode::kMavlinkUdp:
        return "MAVLink UDP";
    case WifiCommMode::kMavlinkUart:
        return "MAVLink UART";
    default:
        return "Unknown";
    }
}

QueueHandle_t q_imu_state = nullptr;
QueueHandle_t q_motion_state = nullptr;
QueueHandle_t q_ultrasonic_state = nullptr;
QueueHandle_t q_lidar_state = nullptr;   
QueueHandle_t q_gamepad_state = nullptr;
QueueHandle_t q_temperature_state = nullptr;
QueueHandle_t q_battery_state = nullptr;


QueueHandle_t q_motion_cmd = nullptr;
QueueHandle_t q_servo_cmd = nullptr;
QueueHandle_t q_speedpid_cmd = nullptr;
QueueHandle_t q_postionpid_cmd = nullptr;

PidMsg g_speed_pid_state = {
    .kp = 1.0f,
    .ki = 6.0f,
    .kd = 0.0f,
};

PidMsg g_position_pid_state = {
    .kp = 2.1f,
    .ki = 0.0f,
    .kd = 0.5f,
};
