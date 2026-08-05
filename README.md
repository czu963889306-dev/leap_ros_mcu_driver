# leap_ros_mcu_driver

Software version: `v1.4`

ESP32-S3 MCU driver firmware for Leap low-level control. The firmware supports micro-ROS and MAVLink communication modes, exposes motion, IMU, lidar, ultrasonic, battery, and status data, and provides a Wi-Fi provisioning portal for runtime configuration.

## v1.4

- 添加 MAVLink 串口协议，方便接入树莓派、香橙派等主板进行控制。
- 支持 MAVLink UDP、MAVLink UART 与 micro-ROS 通信模式切换。
- 支持长按 BOOT 键清除 Wi-Fi 配置并重启回到配网模式。

## Protocols

See [doc/protocols.md](doc/protocols.md) for MAVLink and micro-ROS message details.
