#pragma once

#include <stddef.h>
#include <stdint.h>
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/uart.h"

namespace leap_config {
namespace network {

static constexpr uint32_t kWifiConnectTimeoutMs = 15000;
static constexpr const char *kWifiCfgNamespace = "wifi_cfg";
static constexpr const char *kWifiCfgSsidKey = "sta_ssid";
static constexpr const char *kWifiCfgPasswordKey = "sta_pass";
static constexpr const char *kWifiCfgProvisionOnlyKey = "provision_only";
static constexpr const char *kRuntimeCfgNamespace = "runtime_cfg";
static constexpr const char *kRuntimeCfgCommModeKey = "comm_mode";
static constexpr const char *kRuntimeCfgMicroRosAgentIpKey = "uros_ip";
static constexpr const char *kRuntimeCfgMicroRosAgentPortKey = "uros_port";
static constexpr const char *kDefaultStaSsid = "Maturo";
static constexpr const char *kDefaultStaPassword = "maturo2026";
static constexpr const char *kDefaultMicroRosAgentIp = "192.168.31.214";
static constexpr uint16_t kDefaultMicroRosAgentPort = 8888;

static constexpr uart_port_t kMicroRosUartPort = UART_NUM_0;
static constexpr gpio_num_t kMicroRosUartTxPin = GPIO_NUM_43;
static constexpr gpio_num_t kMicroRosUartRxPin = GPIO_NUM_44;
static constexpr int kMicroRosUartBaudRate = 921600;
static constexpr size_t kMicroRosUartRxBufferSize = 4096;
static constexpr size_t kMicroRosUartTxBufferSize = 8192;
static constexpr int kMicroRosUartReadMaxWaitMs = 20;
static constexpr uint32_t kMicroRosUartStartupDelayMs = 8000;

static constexpr uart_port_t kMavlinkUartPort = UART_NUM_0;
static constexpr gpio_num_t kMavlinkUartTxPin = GPIO_NUM_43;
static constexpr gpio_num_t kMavlinkUartRxPin = GPIO_NUM_44;
static constexpr int kMavlinkUartBaudRate = 230400;
static constexpr size_t kMavlinkUartRxBufferSize = 2048;
static constexpr size_t kMavlinkUartTxBufferSize = 8192;
static constexpr size_t kMavlinkReadBufferSize = 256;

// Keep the existing menuconfig override for the micro-ROS local UDP port.
#ifdef CONFIG_MICRO_ROS_LOCAL_PORT
static constexpr const char kMicroRosLocalPort[] = CONFIG_MICRO_ROS_LOCAL_PORT;
#else
static constexpr const char kMicroRosLocalPort[] = "8888";
#endif
static constexpr uint16_t kMavlinkUdpPort = 14550;
static constexpr size_t kMavlinkUdpRxBufferSize = 32768;
static constexpr uint32_t kMavlinkPublishPeriodMs = 20;
static constexpr uart_port_t kLidarUartPort = UART_NUM_1;
static constexpr int kLidarBaudRate = 115200;
static constexpr uint32_t kLidarTaskPeriodMs = 10;

}  // namespace network
}  // namespace leap_config
