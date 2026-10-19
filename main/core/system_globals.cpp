#include "system_globals.h"

#include <stdio.h>
#include "motion_config.h"
#include "network_config.h"

SystemGlobals::SystemGlobals() {
    namespace motion_cfg = leap_config::motion;
    runtime.microros_agent_port = leap_config::network::kDefaultMicroRosAgentPort;
    snprintf(runtime.microros_agent_ip, sizeof(runtime.microros_agent_ip), "%s",
             leap_config::network::kDefaultMicroRosAgentIp);
    snprintf(runtime.device_name, sizeof(runtime.device_name), "%s", "Maturo_UNKNOWN");
    control.speed_pid = {motion_cfg::kDefaultSpeedKp, motion_cfg::kDefaultSpeedKi, motion_cfg::kDefaultSpeedKd};
    control.position_pid = {motion_cfg::kDefaultPositionKp, motion_cfg::kDefaultPositionKi, motion_cfg::kDefaultPositionKd};
}

SystemGlobals& SystemGlobals::Instance() {
    static SystemGlobals instance;
    return instance;
}

SystemGlobals& system_globals() {
    return SystemGlobals::Instance();
}

bool SystemGlobals::IsWifiCommModeValid(WifiCommMode mode) {
    return mode == WifiCommMode::kMavlinkUdp ||
           mode == WifiCommMode::kMicroRos ||
           mode == WifiCommMode::kMavlinkUart ||
           mode == WifiCommMode::kMicroRosUart;
}

WifiCommMode SystemGlobals::NextWifiCommMode(WifiCommMode mode) {
    switch (mode) {
    case WifiCommMode::kMicroRos:
        return WifiCommMode::kMicroRosUart;
    case WifiCommMode::kMicroRosUart:
        return WifiCommMode::kMavlinkUdp;
    case WifiCommMode::kMavlinkUdp:
        return WifiCommMode::kMavlinkUart;
    case WifiCommMode::kMavlinkUart:
    default:
        return WifiCommMode::kMicroRos;
    }
}

const char *SystemGlobals::WifiCommModeToRuntimeValue(WifiCommMode mode) {
    switch (mode) {
    case WifiCommMode::kMicroRos:
        return "micro_ros";
    case WifiCommMode::kMavlinkUdp:
        return "mavlink_udp";
    case WifiCommMode::kMavlinkUart:
        return "uart_mavlink";
    case WifiCommMode::kMicroRosUart:
        return "microros_uart";
    default:
        return "unknown";
    }
}

const char *SystemGlobals::WifiCommModeToDisplayName(WifiCommMode mode) {
    switch (mode) {
    case WifiCommMode::kMicroRos:
        return "micro-ROS";
    case WifiCommMode::kMavlinkUdp:
        return "MAVLink UDP";
    case WifiCommMode::kMavlinkUart:
        return "MAVLink UART";
    case WifiCommMode::kMicroRosUart:
        return "micro-ROS UART";
    default:
        return "Unknown";
    }
}
