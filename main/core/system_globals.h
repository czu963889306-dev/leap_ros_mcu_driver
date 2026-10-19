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
    kMicroRosUart = 3,
};

struct TargetHostInfo {
    bool valid;
    uint32_t last_update_ms;
    char hostname[32];
    char hostip[16];
    char text[96];
};

struct SystemFlags {
    volatile bool emergency_stop = false;
    volatile bool motion_busy = false;
    volatile bool gamepad_override_active = false;
    volatile uint32_t lidar_scan_sequence = 0;
};

struct RuntimeSettings {
    volatile WifiCommMode wifi_comm_mode = WifiCommMode::kMicroRos;
    char microros_agent_ip[16] = {};
    uint16_t microros_agent_port = 0;
    char device_name[32] = {};
    TargetHostInfo target_host_info = {};
};

struct AppQueues {
    QueueHandle_t imu_state = nullptr;
    QueueHandle_t motion_state = nullptr;
    QueueHandle_t ultrasonic_state = nullptr;
    QueueHandle_t lidar_state = nullptr;
    QueueHandle_t gamepad_state = nullptr;
    QueueHandle_t temperature_state = nullptr;
    QueueHandle_t battery_state = nullptr;
    QueueHandle_t motion_cmd = nullptr;
    QueueHandle_t gamepad_motion_cmd = nullptr;
    QueueHandle_t servo_cmd = nullptr;
    QueueHandle_t speedpid_cmd = nullptr;
    QueueHandle_t positionpid_cmd = nullptr;
};

struct ControlState {
    PidMsg speed_pid = {};
    PidMsg position_pid = {};
};

class SystemGlobals {
 public:
    static SystemGlobals& Instance();
    static bool IsWifiCommModeValid(WifiCommMode mode);
    static WifiCommMode NextWifiCommMode(WifiCommMode mode);
    static const char *WifiCommModeToRuntimeValue(WifiCommMode mode);
    static const char *WifiCommModeToDisplayName(WifiCommMode mode);

    SystemFlags flags;
    RuntimeSettings runtime;
    AppQueues queues;
    ControlState control;
    portMUX_TYPE target_host_info_lock = portMUX_INITIALIZER_UNLOCKED;

 private:
    SystemGlobals();
};

SystemGlobals& system_globals();

// Task entry declarations.
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
