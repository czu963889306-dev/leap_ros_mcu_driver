# Leap Low v1 MAVLink 与 micro-ROS 协议说明

软件版本：`v1.5`

本文档说明 `leap_low_v1` 固件提供的网络与串口通信协议。

## 运行模式

固件同一时间只启用一种通信模式：

| 模式 | 运行值 | 默认 |
| --- | --- | --- |
| micro-ROS | `micro_ros` | 是 |
| MAVLink UDP | `mavlink_udp` | 否 |
| MAVLink UART | `uart_mavlink` | 否 |

通信模式保存在 NVS 的运行配置中，可通过网页配置页面修改。默认 micro-ROS agent 地址为 `192.168.31.214:8888`。

## 单位约定

| 数据 | 内部单位 | MAVLink 单位 | ROS 单位 |
| --- | --- | --- | --- |
| 线性位置 | mm | m | m |
| 线速度 | mm/s | m/s | m/s |
| 航向角 / 角速度 | rad / rad/s | rad / rad/s | rad / rad/s |
| IMU 加速度 | g | `SCALED_IMU` 中为 mg，ROS 中为 m/s^2 | m/s^2 |
| IMU 陀螺仪 | deg/s | rad/s 或 mrad/s | rad/s |
| 雷达距离 | mm | `OBSTACLE_DISTANCE` 中为 cm | m |
| 电池电压 | V | mV | V |

## micro-ROS

传输方式：基于 Wi-Fi 的自定义 UDP 传输。

| 项目 | 值 |
| --- | --- |
| 节点名称 | `leap_low_driver` |
| 本地 UDP 端口 | `CONFIG_MICRO_ROS_LOCAL_PORT`，默认 `8888` |
| Agent 地址 | 运行时 `g_microros_agent_ip:g_microros_agent_port`，默认 `192.168.31.214:8888` |
| 定时器周期 | 20 ms |

### 订阅话题

| 话题 | 类型 | QoS | 映射 |
| --- | --- | --- | --- |
| `/cmd_vel` | `geometry_msgs/msg/Twist` | sensor data | `linear.x/y` 由 m/s 转为目标 `vx/vy`，单位 mm/s；`angular.z` 转为目标 `wz`，单位 rad/s |

收到 `/cmd_vel` 后会向 `q_motion_cmd` 写入速度指令，将控制来源标记为 micro-ROS，并清除 `g_emergency_stop`。

### 发布话题

| 话题 | 类型 | 频率 | 坐标系 | 说明 |
| --- | --- | --- | --- | --- |
| `/odom` | `nav_msgs/msg/Odometry` | 50 Hz | `odom`，子坐标系 `base_link` | 来自运动状态的位置与速度 |
| `/imu` | `sensor_msgs/msg/Imu` | 50 Hz | `imu_link` | 四元数、陀螺仪、加速度 |
| `/scan` | `sensor_msgs/msg/LaserScan` | 10 Hz | `laser_frame` | 360 个点，角度增量 1 度，范围 0.02-12.0 m |
| `/battery_state` | `sensor_msgs/msg/BatteryState` | 10 Hz | `battery` | 电压与电量百分比；锂电池，放电状态 |
| `/ultrasonic` | `sensor_msgs/msg/Range` | 10 Hz | `ultrasonic_link` | HC-SR04 超声波距离，单位 m |

`/battery_state` 字段：

| 字段 | 值 |
| --- | --- |
| `voltage` | 实测电池电压，单位 V |
| `percentage` | `0.0` 到 `1.0` |
| `power_supply_status` | `DISCHARGING` |
| `power_supply_health` | `GOOD` |
| `power_supply_technology` | `LIPO` |
| `present` | `true` |
| `temperature/current/charge/capacity/design_capacity` | `NaN` |

## MAVLink UDP

传输方式：绑定到 `14550` 端口的 UDP socket。

| 项目 | 值 |
| --- | --- |
| 本地端口 | `14550` |
| 初始目标 | 广播地址 `255.255.255.255:14550` |
| 已连接目标 | 第一个发送 MAVLink 数据的地址 |
| System ID | `1` |
| Component ID | `1` |
| 主循环周期 | 20 ms |
| 车辆类型 | `MAV_TYPE_GROUND_ROVER` |
| Autopilot | `MAV_AUTOPILOT_GENERIC` |

## MAVLink UART

传输方式：`UART0`，波特率 `230400`，8N1。运行日志与 MAVLink UART 共用 UART0 串口。

| 项目 | 值 |
| --- | --- |
| TX 引脚 | GPIO43 |
| RX 引脚 | GPIO44 |
| 日志端口 | 共用 UART0 |
| System ID | `1` |
| Component ID | `1` |
| 主循环周期 | 20 ms |

## MAVLink 消息

### 接收消息

| 消息 | 作用 |
| --- | --- |
| `SET_POSITION_TARGET_LOCAL_NED` | 启用 x/y/yaw 字段时作为位置指令；启用 vx/vy/yaw_rate 字段时作为速度指令 |
| `COMMAND_LONG` | 处理解锁/上锁、里程计复位、舵机、直接轮速、相对运动和 PID 更新指令 |
| `PARAM_REQUEST_READ` | 返回单个 PID 参数 |
| `PARAM_REQUEST_LIST` | 返回全部 PID 参数 |
| `PARAM_SET` | 更新单个 PID 参数并返回新值 |

### 服务

| 服务 | 作用 |
| --- | --- |
| `/set_speed_pid` | 设置速度 PID 的 `kp/ki/kd`，并写入 NVS |
| `/get_speed_pid` | 获取当前速度 PID 参数 |

### COMMAND_LONG 指令

| 指令 | 参数 | 结果 |
| --- | --- | --- |
| `MAV_CMD_COMPONENT_ARM_DISARM` | `param1 < 0.5`：停止；否则清除急停 | `ACCEPTED` |
| `MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS` | 无 | 复位里程计 |
| `MAV_CMD_DO_SET_SERVO` | `param2`：舵机角度 | 写入 `q_servo_cmd` |
| `MAV_CMD_DO_SET_ACTUATOR` | `param1`：左轮目标，`param2`：右轮目标 | 轮速模式 |
| `MAV_CMD_USER_2` | `param1`：相对距离，`param2`：相对航向角 | 相对运动模式 |
| `MAV_CMD_USER_4` | `param1`：PID 目标，`param2`：kp，`param3`：ki，`param4`：kd | 更新速度或位置 PID |

自定义指令 ID：

| 名称 | 值 | 含义 |
| --- | --- | --- |
| `MATURO_MAV_CMD_MOVE_RELATIVE` | `MAV_CMD_USER_2` | 相对运动 |
| `MATURO_MAV_CMD_SET_PID` | `MAV_CMD_USER_4` | 设置 PID 参数 |

PID 目标值：

| 值 | 目标 |
| --- | --- |
| `1` | 速度 PID |
| `2` | 位置 PID |

### 参数

MAVLink 参数协议暴露以下参数：

| 参数 | 类型 | 含义 |
| --- | --- | --- |
| `SPD_KP` | `MAV_PARAM_TYPE_REAL32` | 速度 PID kp |
| `SPD_KI` | `MAV_PARAM_TYPE_REAL32` | 速度 PID ki |
| `SPD_KD` | `MAV_PARAM_TYPE_REAL32` | 速度 PID kd |
| `POS_KP` | `MAV_PARAM_TYPE_REAL32` | 位置 PID kp |
| `POS_KI` | `MAV_PARAM_TYPE_REAL32` | 位置 PID ki |
| `POS_KD` | `MAV_PARAM_TYPE_REAL32` | 位置 PID kd |

### 发布消息

有对应源数据时每 20 ms 发布：

| 消息 | 内容 |
| --- | --- |
| `ATTITUDE` | roll/pitch/yaw 与陀螺仪，单位 rad |
| `ATTITUDE_QUATERNION` | 四元数与陀螺仪，单位 rad/s |
| `SCALED_IMU` | 加速度单位 mg，陀螺仪单位 mrad/s，磁力计为 0 |
| `ODOMETRY` | 本地 FLU 位姿与机体 FRD 速度 |

每 100 ms 发布：

| 消息 | 内容 |
| --- | --- |
| `DISTANCE_SENSOR` | 超声波距离，2-400 cm |
| `DEBUG` | index `1`，运动忙状态以 `0.0` 或 `1.0` 表示 |
| `RAW_RPM` | index `0`：左轮 RPM；index `1`：右轮 RPM |

每完成一帧雷达扫描后发布：

| 消息 | 内容 |
| --- | --- |
| `OBSTACLE_DISTANCE` | 360 度雷达扫描拆分为 5 个数据包；每包 72 个 1 度 bin，`angle_offset` 分别为 `0/72/144/216/288` 度 |

每 1 s 发布：

| 消息 | 内容 |
| --- | --- |
| `HEARTBEAT` | 地面车心跳 |
| `STATUSTEXT` | `hostname=<device_name> ip=<sta_ipv4>` |
| `ONBOARD_COMPUTER_STATUS` | 堆内存、Flash、Wi-Fi 链路估计、有效时的板载温度 |
| `SYS_STATUS` | 电池电压，单位 mV；剩余电量百分比 |
| `BATTERY_STATUS` | 锂电池电压与剩余电量百分比 |

首次看到 MAVLink 客户端后发布一次：

| 消息 | 内容 |
| --- | --- |
| `COMPONENT_INFORMATION_BASIC` | vendor `Maturo`，model `Driver`，software `v1.4`，hardware `ESP32`，serial 为设备名 |

MAVLink 发布行为遵循当前启用的通信模式和对应传输方式。

### 电池上报

电池状态基于 GPIO3 ADC 采样：

| 字段 | 值 |
| --- | --- |
| 满电电压 | `8.4 V` |
| 空电估计电压 | `6.0 V` |
| 分压比 | `8.4 / 2.6857` |
| 百分比 | 根据 6.0 V 到 8.4 V 线性估算 |

MAVLink 电池字段：

| 消息 | 字段 | 值 |
| --- | --- | --- |
| `SYS_STATUS` | `voltage_battery` | 电池电压，单位 mV；无效时为 `UINT16_MAX` |
| `SYS_STATUS` | `current_battery` | `-1`，表示未知 |
| `SYS_STATUS` | `battery_remaining` | `0..100`，无效时为 `-1` |
| `BATTERY_STATUS` | `battery_function` | `MAV_BATTERY_FUNCTION_ALL` |
| `BATTERY_STATUS` | `type` | `MAV_BATTERY_TYPE_LIPO` |
| `BATTERY_STATUS` | `voltages[0]` | 电池电压，单位 mV |
| `BATTERY_STATUS` | `current_battery/current_consumed/energy_consumed` | `-1`，表示未知 |
| `BATTERY_STATUS` | `charge_state` | 正常；低电量为 <=20%；严重低电量为 <=10% |

## 模式切换说明

只有当前启用的模式会发送通信数据：

| 当前模式 | 行为 |
| --- | --- |
| `micro_ros` | 创建并运行 micro-ROS 实体；MAVLink UDP 和 MAVLink UART 不发布、不接收 |
| `mavlink_udp` | MAVLink UDP 任务接收和发布；micro-ROS 与 MAVLink UART 不工作 |
| `uart_mavlink` | MAVLink UART 任务接收和发布；micro-ROS 与 MAVLink UDP 不工作 |

网页运行配置会将通信模式和 micro-ROS agent 地址保存到 NVS，重启后仍然生效。

## BOOT 键回到配网模式

运行时长按 BOOT 键约 3 秒会清除已保存的 Wi-Fi STA 配置，状态灯进入快闪。松开 BOOT 键后设备会重启，并进入 Wi-Fi 配网模式。
