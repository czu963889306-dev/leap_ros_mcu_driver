#include "microros_internal.h"

namespace microros {

static bool append_json_char(char *out, size_t out_size, size_t *offset, char ch) {
    if (out == nullptr || offset == nullptr || *offset + 1 >= out_size) {
        return false;
    }
    out[(*offset)++] = ch;
    out[*offset] = '\0';
    return true;
}

static bool append_json_literal(char *out, size_t out_size, size_t *offset, const char *text) {
    if (text == nullptr) {
        return false;
    }
    while (*text != '\0') {
        if (!append_json_char(out, out_size, offset, *text++)) {
            return false;
        }
    }
    return true;
}

static bool append_json_escaped(char *out, size_t out_size, size_t *offset, const char *text) {
    if (text == nullptr) {
        return false;
    }
    while (*text != '\0') {
        const char ch = *text++;
        if ((ch == '"' || ch == '\\') && !append_json_char(out, out_size, offset, '\\')) {
            return false;
        }
        if (!append_json_char(out, out_size, offset, ch)) {
            return false;
        }
    }
    return true;
}

static bool build_wifi_config_payload(char *ssid_out, size_t ssid_out_size) {
    if (ssid_out == nullptr || ssid_out_size == 0) {
        return false;
    }

    char ssid[33] = {};
    char password[65] = {};
    if (wifi_load_sta_credentials_or_default(ssid, sizeof(ssid), password, sizeof(password)) != ESP_OK ||
        ssid[0] == '\0') {
        return false;
    }

    size_t offset = 0;
    s_wifi_config_data[0] = '\0';
    bool ok = append_json_literal(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, "{\"ssid\":\"");
    ok = ok && append_json_escaped(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, ssid);
    ok = ok && append_json_literal(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, "\",\"password\":\"");
    ok = ok && append_json_escaped(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, password);
    ok = ok && append_json_literal(s_wifi_config_data, sizeof(s_wifi_config_data), &offset, "\"}");
    if (!ok) {
        s_wifi_config_data[0] = '\0';
        return false;
    }

    snprintf(ssid_out, ssid_out_size, "%s", ssid);
    return true;
}

static void publish_wifi_config() {
    if (!s_wifi_config_publisher_initialized || s_wifi_config_msg.data.data == nullptr) {
        return;
    }

    char ssid[33] = {};
    if (!build_wifi_config_payload(ssid, sizeof(ssid))) {
        return;
    }

    s_wifi_config_msg.data.size = strlen(s_wifi_config_data);
    s_wifi_config_msg.data.capacity = sizeof(s_wifi_config_data);
    MICROROS_RCSOFTCHECK(rcl_publish(&s_wifi_config_publisher, &s_wifi_config_msg, nullptr));
    if (strcmp(s_last_wifi_config_ssid, ssid) != 0) {
        snprintf(s_last_wifi_config_ssid, sizeof(s_last_wifi_config_ssid), "%s", ssid);
        ESP_LOGI(kTag, "Publishing wifi_config every 1s for SSID: %s", ssid);
    }
}

static void set_stamp(std_msgs__msg__Header *header, int64_t stamp_ms) {
    header->stamp.sec = static_cast<int32_t>(stamp_ms / 1000);
    header->stamp.nanosec = static_cast<uint32_t>((stamp_ms % 1000) * 1000000);
}

static void publish_odom(int64_t stamp_ms) {
    MotionMsg motion = {};
    if (system_globals().queues.motion_state == nullptr || xQueuePeek(system_globals().queues.motion_state, &motion, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_odom_msg.header, stamp_ms);
    s_odom_msg.pose.pose.position.x = motion.x / 1000.0;
    s_odom_msg.pose.pose.position.y = motion.y / 1000.0;
    s_odom_msg.pose.pose.position.z = 0.0;
    s_odom_msg.pose.pose.orientation.w = motion.qw;
    s_odom_msg.pose.pose.orientation.x = motion.qx;
    s_odom_msg.pose.pose.orientation.y = motion.qy;
    s_odom_msg.pose.pose.orientation.z = motion.qz;
    s_odom_msg.twist.twist.linear.x = motion.vx / 1000.0;
    s_odom_msg.twist.twist.linear.y = motion.vy / 1000.0;
    s_odom_msg.twist.twist.angular.z = motion.wz;
    MICROROS_RCSOFTCHECK(rcl_publish(&s_odom_publisher, &s_odom_msg, nullptr));
}

static void publish_imu(int64_t stamp_ms) {
    ImuMsg imu = {};
    if (system_globals().queues.imu_state == nullptr || xQueuePeek(system_globals().queues.imu_state, &imu, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_imu_msg.header, stamp_ms);
    s_imu_msg.orientation.w = imu.qw;
    s_imu_msg.orientation.x = imu.qx;
    s_imu_msg.orientation.y = imu.qy;
    s_imu_msg.orientation.z = imu.qz;
    s_imu_msg.angular_velocity.x = imu.gyro_x * ros_cfg::kDegToRad;
    s_imu_msg.angular_velocity.y = imu.gyro_y * ros_cfg::kDegToRad;
    s_imu_msg.angular_velocity.z = imu.gyro_z * ros_cfg::kDegToRad;
    s_imu_msg.linear_acceleration.x = imu.acc_x * ros_cfg::kGravity;
    s_imu_msg.linear_acceleration.y = imu.acc_y * ros_cfg::kGravity;
    s_imu_msg.linear_acceleration.z = imu.acc_z * ros_cfg::kGravity;
    MICROROS_RCSOFTCHECK(rcl_publish(&s_imu_publisher, &s_imu_msg, nullptr));
}

static void publish_scan(int64_t stamp_ms) {
    LidarMsg lidar = {};
    if (system_globals().queues.lidar_state == nullptr || xQueuePeek(system_globals().queues.lidar_state, &lidar, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_scan_msg.header, stamp_ms);
    for (size_t i = 0; i < ros_cfg::kLaserScanPointCount; ++i) {
        s_scan_msg.ranges.data[i] = lidar.distances[i] > 0
            ? static_cast<float>(lidar.distances[i]) / 1000.0f
            : 0.0f;
    }
    MICROROS_RCSOFTCHECK(rcl_publish(&s_scan_publisher, &s_scan_msg, nullptr));
}

static void publish_battery(int64_t stamp_ms) {
    BatteryMsg battery = {};
    if (system_globals().queues.battery_state == nullptr || xQueuePeek(system_globals().queues.battery_state, &battery, 0) != pdTRUE ||
        !battery.valid) {
        return;
    }

    set_stamp(&s_battery_msg.header, stamp_ms);
    s_battery_msg.voltage = battery.voltage_v;
    s_battery_msg.temperature = NAN;
    s_battery_msg.current = NAN;
    s_battery_msg.charge = NAN;
    s_battery_msg.capacity = NAN;
    s_battery_msg.design_capacity = NAN;
    s_battery_msg.percentage = static_cast<float>(battery.percentage) / 100.0f;
    s_battery_msg.power_supply_status =
        sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_DISCHARGING;
    s_battery_msg.power_supply_health =
        sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_GOOD;
    s_battery_msg.power_supply_technology =
        sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_LIPO;
    s_battery_msg.present = true;
    MICROROS_RCSOFTCHECK(rcl_publish(&s_battery_publisher, &s_battery_msg, nullptr));
}

static void publish_ultrasonic(int64_t stamp_ms) {
    UltrasonicMsg ultrasonic = {};
    if (system_globals().queues.ultrasonic_state == nullptr ||
        xQueuePeek(system_globals().queues.ultrasonic_state, &ultrasonic, 0) != pdTRUE) {
        return;
    }

    set_stamp(&s_ultrasonic_msg.header, stamp_ms);
    s_ultrasonic_msg.range = ultrasonic.distance_cm > 0.0f
        ? ultrasonic.distance_cm / 100.0f
        : NAN;
    MICROROS_RCSOFTCHECK(rcl_publish(&s_ultrasonic_publisher, &s_ultrasonic_msg, nullptr));
}

void publish_state_timer(rcl_timer_t *timer, int64_t) {
    if (timer == nullptr ||
        (system_globals().runtime.wifi_comm_mode != WifiCommMode::kMicroRos &&
         system_globals().runtime.wifi_comm_mode != WifiCommMode::kMicroRosUart)) {
        return;
    }

    const int64_t stamp_ms = rmw_uros_epoch_millis();
    publish_odom(stamp_ms);
    publish_imu(stamp_ms);

    if ((++s_publish_tick % ros_cfg::kSlowPublishDivider) == 0) {
        publish_scan(stamp_ms);
        publish_battery(stamp_ms);
        publish_ultrasonic(stamp_ms);
    }
    if ((s_publish_tick % ros_cfg::kWifiConfigPublishTicks) == 0) {
        publish_wifi_config();
    }
}

}  // namespace microros
