# leap_ros

软件版本：`v2.1`

`leap_ros` 是 Leap_ROS 底盘的 ESP32-S3 下位机驱动固件，用于电机控制、里程计、IMU、雷达、超声波、电池状态、状态灯和外设数据采集。固件支持 micro-ROS 与 MAVLink 通信模式，并提供 Wi-Fi 配网页用于运行参数配置。

## v2.1 更新内容

- 支持通过服务通讯修改速度 PID 参数，并提供获取 PID 参数服务。
- 超声波改为独立 HC-SR04，TRIG 使用 `GPIO21`，ECHO 使用 `GPIO47`。
- micro-ROS 新增 `/ultrasonic` 话题，发布超声波距离数据。
- 支持 MAVLink UDP、MAVLink UART 与 micro-ROS 通信模式切换。
- 支持 micro-ROS UART 模式：复用 MAVLink UART 的 UART0，921600 波特率，系统启动 5 秒后连接 Agent。
- 支持长按 BOOT 键清除 Wi-Fi 配置，并重启回到配网模式。
- 接入 I²C 手柄控制：左摇杆 Y 控制前后，右摇杆 X 控制转向；断连后自动发送零速指令。

## 底盘参数

- 两轮差速底盘：轮径 `65 mm`、轮距 `131.7 mm`、每圈编码器计数 `4680`，集中在 `main/config/motion_config.h`。
- 保留现有 Camsense 雷达（115200 波特率）、电池 ADC、HC-SR04、单舵机、I²C 手柄和四种通信模式。
- 目录组织参考 `leap_ros_four`；硬件参数和协议保持本工程配置，不包含机械臂运动学、机械臂任务或机械臂 ROS 接口。

## 代码结构

```text
main/
├── app_main.cpp / app_runtime.cpp     # 入口、初始化和任务创建
├── config/                           # 编译期配置及 PID 持久化
│   ├── board_config.h                # GPIO、I²C、ADC、外设采样周期
│   ├── motion_config.h               # 两轮几何、编码器、PID 默认值、控制周期
│   ├── network_config.h              # Wi-Fi、NVS 键、串口、端口、启动等待
│   ├── ros_config.h                  # ROS 节点、话题、服务、frame、发布周期
│   └── pid_config.h / pid_config.cpp # 速度 PID 的 NVS 读取和保存
├── core/system_globals.*             # flags / runtime / queues / control 共享状态
├── platform/board.*                  # 硬件对象及初始化
├── control/
│   ├── differential_kinematics.*     # 两轮差速正逆运动学，轮序为左、右
│   └── motion_controller.*           # PID、里程计、位置和相对运动控制
├── network/wifi_app.*                # Wi-Fi 连接及运行配置持久化
├── msg/                              # 任务间消息
└── tasks/
    ├── control/ / sensors/ / io/
    └── network/
        ├── microros/                 # task、runtime、state、transport、发布、订阅、服务
        ├── mavlink/                  # 共用协议处理、UDP 和 UART 任务
        └── provision/                # 任务入口、HTTP/DNS、独立 HTML 页面
```

共享状态通过 `system_globals()` 访问，例如 `system_globals().queues.motion_cmd`、`system_globals().runtime.wifi_comm_mode`。主机信息的临界区锁仍保留。

## 常用配置位置

| 修改内容 | 文件 | 配置项 |
| --- | --- | --- |
| micro-ROS UART 启动等待 | `main/config/network_config.h` | `kMicroRosUartStartupDelayMs`，默认 `5000`；设为 `10000` 即等待 10 秒 |
| Agent 默认地址和端口 | `main/config/network_config.h` | `kDefaultMicroRosAgentIp`、`kDefaultMicroRosAgentPort` |
| micro-ROS / MAVLink 串口波特率 | `main/config/network_config.h` | `kMicroRosUartBaudRate` / `kMavlinkUartBaudRate` |
| 雷达串口和波特率 | `main/config/network_config.h` | `kLidarUartPort`、`kLidarBaudRate` |
| 电机、编码器、传感器引脚 | `main/config/board_config.h` | 对应的 `kMotor*`、`kEncoder*`、`kUltrasonic*` 等 |
| 轮径、轮距、编码器方向 | `main/config/motion_config.h` | `kWheelDiameterMm`、`kTrackWidthMm`、`kEncoderSigns` |
| 速度 PID 默认值 | `main/config/motion_config.h` | `kDefaultSpeedKp`、`kDefaultSpeedKi`、`kDefaultSpeedKd` |
| ROS 名称及发布周期 | `main/config/ros_config.h` | `kNodeName`、`k*Topic`、`k*Service`、`kPublishPeriodMs` |

启动等待只作用于 micro-ROS UART 模式，从通信任务启动时开始计时。编译期参数修改后需要重新编译、烧录。已保存的 Wi-Fi、通信模式、Agent 地址和速度 PID 仍优先使用 NVS 配置；micro-ROS 本地 UDP 端口继续支持 `CONFIG_MICRO_ROS_LOCAL_PORT`。

## 构建与验证

在已加载 ESP-IDF 环境的终端中执行 `idf.py build`。固件为 `build/leap_ros.bin`，整包为 `build/merged-binary.bin`。

两轮运动学可在主机上独立验证，无需连接开发板：

```bash
g++ -std=c++17 -Wall -Wextra -Werror -I main/config -I main/control \
    tests/differential_kinematics_test.cpp main/control/differential_kinematics.cpp \
    -o /tmp/leap_low_kinematics_test
/tmp/leap_low_kinematics_test
```

上板验证应覆盖前进/后退/原地转向、手柄接管、四种通信模式、ROS 电池和超声波话题，以及配网和 PID 保存重启。

## 协议说明

MAVLink 与 micro-ROS 的消息、话题和参数说明见 [doc/protocols.md](doc/protocols.md)。
