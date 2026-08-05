# leap_ros_mcu_driver

软件版本：`v1.4`

`leap_ros_mcu_driver` 是 Leap 底盘的 ESP32-S3 下位机驱动固件，用于电机控制、里程计、IMU、雷达、超声波、电池状态、状态灯和外设数据采集。固件支持 micro-ROS 与 MAVLink 通信模式，并提供 Wi-Fi 配网页用于运行参数配置。

## v1.4 更新内容

- 添加 MAVLink 串口协议，方便接入树莓派、香橙派等主板进行控制。
- 支持 MAVLink UDP、MAVLink UART 与 micro-ROS 通信模式切换。
- 支持长按 BOOT 键清除 Wi-Fi 配置，并重启回到配网模式。

## 协议说明

MAVLink 与 micro-ROS 的消息、话题和参数说明见 [doc/protocols.md](doc/protocols.md)。
