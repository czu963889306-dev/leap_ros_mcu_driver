#include "provision_portal.h"
#include "provision_portal_page.h"
#include "system_globals.h"
#include "camera_i2c_client.h"
#include "wifi_app.h"
#include "msg/battery_msg.h"
#include "msg/gamepad_msg.h"
#include "msg/imu_msg.h"
#include "msg/lidar_msg.h"
#include "msg/motion_msg.h"
#include "msg/temperature_msg.h"
#include "msg/ultrasonic_msg.h"

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "esp_http_server.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_partition.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"

static const char *TAG = "WIFI_PROVISION";
static constexpr size_t kMaxScanResults = 20;
static constexpr size_t kDnsPacketMaxSize = 512;
static constexpr size_t kScanJsonSize = 4096;
static constexpr size_t kStatusJsonSize = 8192;

static SemaphoreHandle_t s_http_buffer_mutex = nullptr;
static wifi_ap_record_t s_scan_records[kMaxScanResults] = {};
static char s_scan_json[kScanJsonSize] = {};
static char s_status_json[kStatusJsonSize] = {};



static void restart_after_delay_task(void *pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(1200));
    esp_restart();
}

static int hex_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    if (c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');
    }
    return -1;
}

static void url_decode(const char *src, char *dst, size_t dst_size) {
    if (dst_size == 0) {
        return;
    }

    size_t di = 0;
    for (size_t si = 0; src[si] != '\0' && di + 1 < dst_size; ++si) {
        if (src[si] == '+') {
            dst[di++] = ' ';
        } else if (src[si] == '%' && isxdigit(static_cast<unsigned char>(src[si + 1])) &&
                   isxdigit(static_cast<unsigned char>(src[si + 2]))) {
            const int hi = hex_to_int(src[si + 1]);
            const int lo = hex_to_int(src[si + 2]);
            if (hi >= 0 && lo >= 0) {
                dst[di++] = static_cast<char>((hi << 4) | lo);
                si += 2;
            }
        } else {
            dst[di++] = src[si];
        }
    }
    dst[di] = '\0';
}

static bool extract_form_field(const char *body, const char *key, char *out, size_t out_size) {
    const size_t key_len = strlen(key);
    const char *cursor = body;
    while (cursor != NULL && *cursor != '\0') {
        const bool key_matches = strncmp(cursor, key, key_len) == 0 && cursor[key_len] == '=';
        if (key_matches) {
            const char *value_start = cursor + key_len + 1;
            const char *value_end = strchr(value_start, '&');
            const size_t raw_len = (value_end == NULL) ? strlen(value_start)
                                                       : static_cast<size_t>(value_end - value_start);

            char raw_value[256] = {0};
            const size_t copy_len =
                (raw_len < sizeof(raw_value) - 1) ? raw_len : sizeof(raw_value) - 1;
            memcpy(raw_value, value_start, copy_len);
            raw_value[copy_len] = '\0';
            url_decode(raw_value, out, out_size);
            return true;
        }

        cursor = strchr(cursor, '&');
        if (cursor != NULL) {
            ++cursor;
        }
    }

    if (out_size > 0) {
        out[0] = '\0';
    }
    return false;
}

static bool is_lang_en(const char *lang) {
    return lang != NULL && (strcmp(lang, "en") == 0 || strcmp(lang, "en-US") == 0);
}

static bool parse_comm_mode(const char *value, WifiCommMode *mode) {
    if (value == NULL || mode == NULL) {
        return false;
    }
    if (strcmp(value, "micro_ros") == 0 || strcmp(value, "microros") == 0) {
        *mode = WifiCommMode::kMicroRos;
        return true;
    }
    if (strcmp(value, "microros_uart") == 0 || strcmp(value, "micro_ros_uart") == 0) {
        *mode = WifiCommMode::kMicroRosUart;
        return true;
    }
    if (strcmp(value, "mavlink_udp") == 0 || strcmp(value, "mavlink") == 0) {
        *mode = WifiCommMode::kMavlinkUdp;
        return true;
    }
    if (strcmp(value, "uart_mavlink") == 0 || strcmp(value, "mavlink_uart") == 0) {
        *mode = WifiCommMode::kMavlinkUart;
        return true;
    }
    return false;
}

static bool parse_camera_provision_format(const char *value, camera_i2c_provision_format_t *format) {
    if (value == NULL || format == NULL) {
        return false;
    }
    if (strcmp(value, "wifi") == 0 || strcmp(value, "WIFI") == 0) {
        *format = CAMERA_I2C_PROVISION_WIFI;
        return true;
    }
    if (strcmp(value, "set_wifi") == 0 || strcmp(value, "SET_WIFI") == 0) {
        *format = CAMERA_I2C_PROVISION_SET_WIFI;
        return true;
    }
    if (strcmp(value, "prov") == 0 || strcmp(value, "PROV") == 0) {
        *format = CAMERA_I2C_PROVISION_PROV;
        return true;
    }
    if (strcmp(value, "json") == 0 || strcmp(value, "JSON") == 0) {
        *format = CAMERA_I2C_PROVISION_JSON;
        return true;
    }
    return false;
}

static bool is_valid_ipv4_address(const char *ip) {
    if (ip == NULL || ip[0] == '\0') {
        return false;
    }

    in_addr addr = {};
    return inet_pton(AF_INET, ip, &addr) == 1;
}

static bool append_text(char *buffer, size_t buffer_size, int *offset, const char *text) {
    if (buffer == NULL || offset == NULL || text == NULL || *offset < 0) {
        return false;
    }

    const int written = snprintf(buffer + *offset, buffer_size - static_cast<size_t>(*offset), "%s", text);
    if (written < 0 || static_cast<size_t>(*offset + written) >= buffer_size) {
        return false;
    }

    *offset += written;
    return true;
}

static bool append_format(char *buffer, size_t buffer_size, int *offset, const char *format, ...) {
    if (buffer == NULL || offset == NULL || format == NULL || *offset < 0) {
        return false;
    }

    va_list args;
    va_start(args, format);
    const int written =
        vsnprintf(buffer + *offset, buffer_size - static_cast<size_t>(*offset), format, args);
    va_end(args);

    if (written < 0 || static_cast<size_t>(*offset + written) >= buffer_size) {
        return false;
    }

    *offset += written;
    return true;
}

static bool append_json_string(char *buffer, size_t buffer_size, int *offset, const char *text) {
    if (!append_text(buffer, buffer_size, offset, "\"")) {
        return false;
    }

    for (const unsigned char *cursor = reinterpret_cast<const unsigned char *>(text);
         cursor != NULL && *cursor != '\0'; ++cursor) {
        if (*cursor == '\\' || *cursor == '"') {
            if (!append_format(buffer, buffer_size, offset, "\\%c", *cursor)) {
                return false;
            }
        } else if (*cursor < 0x20) {
            if (!append_format(buffer, buffer_size, offset, "\\u%04x", *cursor)) {
                return false;
            }
        } else {
            const char ch[2] = {static_cast<char>(*cursor), '\0'};
            if (!append_text(buffer, buffer_size, offset, ch)) {
                return false;
            }
        }
    }

    return append_text(buffer, buffer_size, offset, "\"");
}

static const char *auth_mode_to_string(wifi_auth_mode_t authmode) {
    switch (authmode) {
        case WIFI_AUTH_OPEN:
            return "OPEN";
        case WIFI_AUTH_WEP:
            return "WEP";
        case WIFI_AUTH_WPA_PSK:
            return "WPA";
        case WIFI_AUTH_WPA2_PSK:
            return "WPA2";
        case WIFI_AUTH_WPA_WPA2_PSK:
            return "WPA/WPA2";
#ifdef WIFI_AUTH_WPA2_ENTERPRISE
        case WIFI_AUTH_WPA2_ENTERPRISE:
            return "WPA2-ENT";
#endif
#ifdef WIFI_AUTH_WPA3_PSK
        case WIFI_AUTH_WPA3_PSK:
            return "WPA3";
#endif
#ifdef WIFI_AUTH_WPA2_WPA3_PSK
        case WIFI_AUTH_WPA2_WPA3_PSK:
            return "WPA2/WPA3";
#endif
#ifdef WIFI_AUTH_WAPI_PSK
        case WIFI_AUTH_WAPI_PSK:
            return "WAPI";
#endif
        default:
            return "UNKNOWN";
    }
}

static uint32_t bytes_to_kib(uint64_t bytes) {
    return static_cast<uint32_t>(bytes / 1024ULL);
}

static uint32_t get_partition_used_kib() {
    uint64_t used_bytes = 0;
    esp_partition_iterator_t it = esp_partition_find(
        ESP_PARTITION_TYPE_ANY,
        ESP_PARTITION_SUBTYPE_ANY,
        nullptr);
    while (it != nullptr) {
        const esp_partition_t *partition = esp_partition_get(it);
        if (partition != nullptr) {
            used_bytes += partition->size;
        }
        it = esp_partition_next(it);
    }
    esp_partition_iterator_release(it);
    return bytes_to_kib(used_bytes);
}

static uint32_t get_flash_total_kib() {
    uint32_t flash_size = 0;
    if (esp_flash_get_size(nullptr, &flash_size) != ESP_OK) {
        return 0;
    }
    return bytes_to_kib(flash_size);
}

static const char *wifi_mode_to_string(wifi_mode_t mode) {
    switch (mode) {
        case WIFI_MODE_NULL:
            return "NULL";
        case WIFI_MODE_STA:
            return "STA";
        case WIFI_MODE_AP:
            return "AP";
        case WIFI_MODE_APSTA:
            return "APSTA";
        default:
            return "UNKNOWN";
    }
}

static bool append_camera_status_json(
    char *buffer,
    size_t buffer_size,
    int *offset,
    const CameraI2cStatus *camera) {
    if (camera == nullptr) {
        return false;
    }

    bool ok = append_text(buffer, buffer_size, offset, "{\"reachable\":");
    ok = ok && append_text(buffer, buffer_size, offset, camera->reachable ? "true" : "false");
    ok = ok && append_text(buffer, buffer_size, offset, ",\"valid\":");
    ok = ok && append_text(buffer, buffer_size, offset, camera->valid ? "true" : "false");
    ok = ok && append_format(
        buffer,
        buffer_size,
        offset,
        ",\"last_update_ms\":%lu,\"last_error\":%d,\"error\":",
        static_cast<unsigned long>(camera->last_update_ms),
        static_cast<int>(camera->last_error));
    ok = ok && append_json_string(buffer, buffer_size, offset, esp_err_to_name(camera->last_error));
    ok = ok && append_text(buffer, buffer_size, offset, ",\"ip\":");
    ok = ok && append_json_string(buffer, buffer_size, offset, camera->ip);
    ok = ok && append_text(buffer, buffer_size, offset, ",\"mode\":");
    ok = ok && append_json_string(buffer, buffer_size, offset, camera->mode);
    ok = ok && append_text(buffer, buffer_size, offset, ",\"name\":");
    ok = ok && append_json_string(buffer, buffer_size, offset, camera->name);
    ok = ok && append_text(buffer, buffer_size, offset, ",\"config_url\":");
    ok = ok && append_json_string(buffer, buffer_size, offset, camera->config_url);
    ok = ok && append_text(buffer, buffer_size, offset, ",\"stream_url\":");
    ok = ok && append_json_string(buffer, buffer_size, offset, camera->stream_url);
    return ok && append_text(buffer, buffer_size, offset, "}");
}

static esp_err_t send_provision_page(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
    httpd_resp_set_hdr(req, "Pragma", "no-cache");
    httpd_resp_set_hdr(req, "Expires", "0");

    const char *cursor = kProvisionHtmlTemplate;
    const char *placeholder = nullptr;
    while ((placeholder = strchr(cursor, '%')) != nullptr) {
        if (placeholder > cursor) {
            esp_err_t err = httpd_resp_send_chunk(
                req, cursor, static_cast<ssize_t>(placeholder - cursor));
            if (err != ESP_OK) {
                return err;
            }
        }

        if (placeholder[1] == 's') {
            esp_err_t err = httpd_resp_send_chunk(req, system_globals().runtime.device_name, HTTPD_RESP_USE_STRLEN);
            if (err != ESP_OK) {
                return err;
            }
            cursor = placeholder + 2;
        } else if (placeholder[1] == '%') {
            esp_err_t err = httpd_resp_send_chunk(req, "%", 1);
            if (err != ESP_OK) {
                return err;
            }
            cursor = placeholder + 2;
        } else {
            esp_err_t err = httpd_resp_send_chunk(req, "%", 1);
            if (err != ESP_OK) {
                return err;
            }
            cursor = placeholder + 1;
        }
    }

    if (*cursor != '\0') {
        esp_err_t err = httpd_resp_send_chunk(req, cursor, HTTPD_RESP_USE_STRLEN);
        if (err != ESP_OK) {
            return err;
        }
    }
    return httpd_resp_send_chunk(req, nullptr, 0);
}

static esp_err_t root_get_handler(httpd_req_t *req) {
    return send_provision_page(req);
}

static esp_err_t scan_get_handler(httpd_req_t *req) {
    if (s_http_buffer_mutex == nullptr ||
        xSemaphoreTake(s_http_buffer_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "busy");
        return ESP_FAIL;
    }

    uint16_t ap_count = kMaxScanResults;
    memset(s_scan_records, 0, sizeof(s_scan_records));

    esp_err_t err = esp_wifi_scan_start(NULL, true);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Wi-Fi scan start failed: %s", esp_err_to_name(err));
        xSemaphoreGive(s_http_buffer_mutex);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "scan start failed");
        return ESP_FAIL;
    }

    err = esp_wifi_scan_get_ap_records(&ap_count, s_scan_records);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Wi-Fi scan read failed: %s", esp_err_to_name(err));
        xSemaphoreGive(s_http_buffer_mutex);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "scan read failed");
        return ESP_FAIL;
    }

    memset(s_scan_json, 0, sizeof(s_scan_json));

    int offset = 0;
    bool ok = append_text(s_scan_json, kScanJsonSize, &offset, "{\"device\":");
    ok = ok && append_json_string(s_scan_json, kScanJsonSize, &offset, system_globals().runtime.device_name);
    ok = ok && append_text(s_scan_json, kScanJsonSize, &offset, ",\"networks\":[");

    size_t emitted = 0;
    for (uint16_t i = 0; ok && i < ap_count; ++i) {
        if (s_scan_records[i].ssid[0] == '\0') {
            continue;
        }
        ok = ok && append_text(s_scan_json, kScanJsonSize, &offset, (emitted == 0) ? "" : ",");
        ok = ok && append_text(s_scan_json, kScanJsonSize, &offset, "{\"ssid\":");
        ok = ok && append_json_string(s_scan_json, kScanJsonSize, &offset,
                                      reinterpret_cast<const char *>(s_scan_records[i].ssid));
        ok = ok && append_format(s_scan_json, kScanJsonSize, &offset, ",\"rssi\":%d", s_scan_records[i].rssi);
        ok = ok && append_text(s_scan_json, kScanJsonSize, &offset, ",\"auth\":");
        ok = ok && append_json_string(s_scan_json, kScanJsonSize, &offset,
                                      auth_mode_to_string(s_scan_records[i].authmode));
        ok = ok && append_format(s_scan_json, kScanJsonSize, &offset, ",\"open\":%s}",
                                 (s_scan_records[i].authmode == WIFI_AUTH_OPEN) ? "true" : "false");
        if (ok) {
            ++emitted;
        }
    }

    ok = ok && append_text(s_scan_json, kScanJsonSize, &offset, "]}");
    if (!ok) {
        xSemaphoreGive(s_http_buffer_mutex);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "scan payload too large");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    const esp_err_t send_err = httpd_resp_send(req, s_scan_json, HTTPD_RESP_USE_STRLEN);
    xSemaphoreGive(s_http_buffer_mutex);
    return send_err;
}

static esp_err_t status_get_handler(httpd_req_t *req) {
    if (s_http_buffer_mutex == nullptr ||
        xSemaphoreTake(s_http_buffer_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "busy");
        return ESP_FAIL;
    }
    memset(s_status_json, 0, sizeof(s_status_json));

    wifi_mode_t wifi_mode = WIFI_MODE_NULL;
    esp_wifi_get_mode(&wifi_mode);

    wifi_ap_record_t ap_info = {};
    const bool sta_connected = (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK);

    esp_netif_ip_info_t ap_ip_info = {};
    const bool has_ap_ip = (wifi_get_softap_ip_info(&ap_ip_info) == ESP_OK);

    ImuMsg imu = {};
    MotionMsg motion = {};
    UltrasonicMsg ultrasonic = {};
    GamepadMsg gamepad = {};
    TemperatureMsg temperature = {};
    BatteryMsg battery = {};
    LidarMsg lidar = {};
    TargetHostInfo target_host = {};
    portENTER_CRITICAL(&system_globals().target_host_info_lock);
    target_host = system_globals().runtime.target_host_info;
    portEXIT_CRITICAL(&system_globals().target_host_info_lock);

    const bool has_imu = system_globals().queues.imu_state != nullptr && xQueuePeek(system_globals().queues.imu_state, &imu, 0) == pdTRUE;
    const bool has_motion = system_globals().queues.motion_state != nullptr && xQueuePeek(system_globals().queues.motion_state, &motion, 0) == pdTRUE;
    const bool has_ultrasonic = system_globals().queues.ultrasonic_state != nullptr && xQueuePeek(system_globals().queues.ultrasonic_state, &ultrasonic, 0) == pdTRUE;
    const bool has_gamepad = system_globals().queues.gamepad_state != nullptr && xQueuePeek(system_globals().queues.gamepad_state, &gamepad, 0) == pdTRUE;
    const bool has_temperature = system_globals().queues.temperature_state != nullptr &&
                                 xQueuePeek(system_globals().queues.temperature_state, &temperature, 0) == pdTRUE &&
                                 temperature.valid;
    const bool has_battery = system_globals().queues.battery_state != nullptr &&
                             xQueuePeek(system_globals().queues.battery_state, &battery, 0) == pdTRUE &&
                             battery.valid;
    const bool has_lidar = system_globals().queues.lidar_state != nullptr && xQueuePeek(system_globals().queues.lidar_state, &lidar, 0) == pdTRUE;

    CameraI2cStatus camera = {};
    esp_err_t camera_err = camera_i2c_client_get_cached_status(&camera);
    if (camera_err != ESP_OK) {
        camera.valid = false;
        camera.reachable = false;
        camera.last_error = camera_err;
    }

    uint16_t lidar_valid_points = 0;
    uint16_t lidar_min_mm = UINT16_MAX;
    uint16_t lidar_max_mm = 0;
    if (has_lidar) {
        for (size_t i = 0; i < sizeof(lidar.distances) / sizeof(lidar.distances[0]); ++i) {
            const uint16_t distance = lidar.distances[i];
            if (distance == 0) {
                continue;
            }
            ++lidar_valid_points;
            if (distance < lidar_min_mm) {
                lidar_min_mm = distance;
            }
            if (distance > lidar_max_mm) {
                lidar_max_mm = distance;
            }
        }
    }
    if (lidar_valid_points == 0) {
        lidar_min_mm = 0;
    }

    const size_t heap_total = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    const size_t heap_free = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    const size_t heap_used = heap_total > heap_free ? heap_total - heap_free : 0;
    const uint32_t flash_total_kib = get_flash_total_kib();
    const uint32_t flash_used_kib = get_partition_used_kib();

    int offset = 0;
    bool ok = append_text(s_status_json, kStatusJsonSize, &offset, "{\"device_name\":");
    ok = ok && append_json_string(s_status_json, kStatusJsonSize, &offset, system_globals().runtime.device_name);
    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"uptime_ms\":%lu,\"emergency_stop\":%s,\"motion_busy\":%s,\"wifi_comm_mode\":",
        static_cast<unsigned long>(xTaskGetTickCount() * portTICK_PERIOD_MS),
        system_globals().flags.emergency_stop ? "true" : "false",
        system_globals().flags.motion_busy ? "true" : "false");
    ok = ok && append_json_string(
        s_status_json,
        kStatusJsonSize,
        &offset,
        SystemGlobals::WifiCommModeToRuntimeValue(system_globals().runtime.wifi_comm_mode));
    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"runtime\":{\"comm_mode\":");
    ok = ok && append_json_string(
        s_status_json,
        kStatusJsonSize,
        &offset,
        SystemGlobals::WifiCommModeToRuntimeValue(system_globals().runtime.wifi_comm_mode));
    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"microros_agent_ip\":");
    ok = ok && append_json_string(s_status_json, kStatusJsonSize, &offset, system_globals().runtime.microros_agent_ip);
    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"microros_agent_port\":%u}",
        static_cast<unsigned>(system_globals().runtime.microros_agent_port));

    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"wifi\":{\"mode\":");
    ok = ok && append_json_string(s_status_json, kStatusJsonSize, &offset, wifi_mode_to_string(wifi_mode));
    ok = ok && append_format(s_status_json, kStatusJsonSize, &offset, ",\"sta_connected\":%s", sta_connected ? "true" : "false");
    if (sta_connected) {
        ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"ssid\":");
        ok = ok && append_json_string(s_status_json, kStatusJsonSize, &offset, reinterpret_cast<const char *>(ap_info.ssid));
        ok = ok && append_format(s_status_json, kStatusJsonSize, &offset, ",\"rssi\":%d,\"channel\":%u", ap_info.rssi, ap_info.primary);
    }
    if (has_ap_ip) {
        ok = ok && append_format(
            s_status_json,
            kStatusJsonSize,
            &offset,
            ",\"ap_ip\":\"" IPSTR "\"",
            IP2STR(&ap_ip_info.ip));
    }
    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, "}");

    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"camera\":");
    ok = ok && append_camera_status_json(s_status_json, kStatusJsonSize, &offset, &camera);

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"memory\":{\"heap_total_kib\":%lu,\"heap_free_kib\":%lu,\"heap_used_kib\":%lu,\"heap_min_free_kib\":%lu}",
        static_cast<unsigned long>(bytes_to_kib(heap_total)),
        static_cast<unsigned long>(bytes_to_kib(heap_free)),
        static_cast<unsigned long>(bytes_to_kib(heap_used)),
        static_cast<unsigned long>(bytes_to_kib(heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT))));

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"storage\":{\"flash_total_kib\":%lu,\"partition_used_kib\":%lu}",
        static_cast<unsigned long>(flash_total_kib),
        static_cast<unsigned long>(flash_used_kib));

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"temperature\":{\"valid\":%s,\"celsius\":%.2f}",
        has_temperature ? "true" : "false",
        has_temperature ? temperature.celsius : 0.0f);

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"battery\":{\"valid\":%s,\"voltage_v\":%.3f,\"adc_voltage_v\":%.4f,\"percentage\":%u,\"raw\":%d}",
        has_battery ? "true" : "false",
        has_battery ? battery.voltage_v : 0.0f,
        has_battery ? battery.adc_voltage_v : 0.0f,
        has_battery ? battery.percentage : 0,
        has_battery ? battery.raw : 0);

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"imu\":{\"valid\":%s,\"roll\":%.2f,\"pitch\":%.2f,\"yaw\":%.2f,\"acc_x\":%.3f,\"acc_y\":%.3f,\"acc_z\":%.3f,\"gyro_x\":%.3f,\"gyro_y\":%.3f,\"gyro_z\":%.3f}",
        has_imu ? "true" : "false",
        imu.roll,
        imu.pitch,
        imu.yaw,
        imu.acc_x,
        imu.acc_y,
        imu.acc_z,
        imu.gyro_x,
        imu.gyro_y,
        imu.gyro_z);

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"motion\":{\"valid\":%s,\"source\":%u,\"control_mode\":%u,\"vx\":%.2f,\"vy\":%.2f,\"wz\":%.3f,\"x\":%.2f,\"y\":%.2f,\"yaw\":%.2f,\"target_vx\":%.2f,\"target_vy\":%.2f,\"target_wz\":%.3f,\"target_x\":%.2f,\"target_y\":%.2f,\"target_yaw\":%.2f,\"vel_left\":%.2f,\"vel_right\":%.2f}",
        has_motion ? "true" : "false",
        motion.source,
        motion.control_mode,
        motion.vx,
        motion.vy,
        motion.wz,
        motion.x,
        motion.y,
        motion.yaw,
        motion.target_vx,
        motion.target_vy,
        motion.target_wz,
        motion.target_x,
        motion.target_y,
        motion.target_yaw,
        motion.vel_left,
        motion.vel_right);

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"ultrasonic\":{\"valid\":%s,\"distance_cm\":%.2f,\"obstacle\":%s}",
        has_ultrasonic ? "true" : "false",
        ultrasonic.distance_cm,
        ultrasonic.is_obstacle_detected ? "true" : "false");

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"gamepad\":{\"valid\":%s,\"connected\":%s,\"left_x\":%d,\"left_y\":%d,\"right_x\":%d,\"right_y\":%d,\"buttons\":%u,\"button_mask\":%u,\"update_ms\":%lu}",
        has_gamepad ? "true" : "false",
        gamepad.connected ? "true" : "false",
        gamepad.left_x,
        gamepad.left_y,
        gamepad.right_x,
        gamepad.right_y,
        gamepad.buttons,
        gamepad.button_mask,
        static_cast<unsigned long>(gamepad.update_ms));

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"lidar\":{\"valid\":%s,\"valid_points\":%u,\"min_mm\":%u,\"max_mm\":%u}",
        has_lidar ? "true" : "false",
        lidar_valid_points,
        lidar_min_mm,
        lidar_max_mm);

    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        ",\"pid\":{\"speed\":{\"kp\":%.4f,\"ki\":%.4f,\"kd\":%.4f},\"position\":{\"kp\":%.4f,\"ki\":%.4f,\"kd\":%.4f}}",
        system_globals().control.speed_pid.kp,
        system_globals().control.speed_pid.ki,
        system_globals().control.speed_pid.kd,
        system_globals().control.position_pid.kp,
        system_globals().control.position_pid.ki,
        system_globals().control.position_pid.kd);

    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"target_host\":{");
    ok = ok && append_format(
        s_status_json,
        kStatusJsonSize,
        &offset,
        "\"valid\":%s,\"last_update_ms\":%lu,\"hostname\":",
        target_host.valid ? "true" : "false",
        static_cast<unsigned long>(target_host.last_update_ms));
    ok = ok && append_json_string(
        s_status_json,
        kStatusJsonSize,
        &offset,
        target_host.hostname);
    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"hostip\":");
    ok = ok && append_json_string(s_status_json, kStatusJsonSize, &offset, target_host.hostip);
    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, ",\"text\":");
    ok = ok && append_json_string(s_status_json, kStatusJsonSize, &offset, target_host.text);
    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, "}");

    ok = ok && append_text(s_status_json, kStatusJsonSize, &offset, "}");
    if (!ok) {
        xSemaphoreGive(s_http_buffer_mutex);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "status payload too large");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    const esp_err_t send_err = httpd_resp_send(req, s_status_json, HTTPD_RESP_USE_STRLEN);
    xSemaphoreGive(s_http_buffer_mutex);
    return send_err;
}

static esp_err_t provision_post_handler(httpd_req_t *req) {
    if (req->content_len <= 0 || req->content_len >= 256) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid payload");
        return ESP_FAIL;
    }

    char body[256] = {0};
    const int received = httpd_req_recv(req, body, req->content_len);
    if (received <= 0) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "read failed");
        return ESP_FAIL;
    }
    body[received] = '\0';

    char ssid[33] = {0};
    char password[65] = {0};
    char lang[8] = {0};
    extract_form_field(body, "ssid", ssid, sizeof(ssid));
    extract_form_field(body, "password", password, sizeof(password));
    extract_form_field(body, "lang", lang, sizeof(lang));

    if (ssid[0] == '\0') {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "ssid required");
        return ESP_FAIL;
    }
    if (password[0] != '\0' && strlen(password) < 8) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "password too short");
        return ESP_FAIL;
    }

    esp_err_t err = wifi_save_sta_credentials(ssid, password);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to save Wi-Fi credentials: %s", esp_err_to_name(err));
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "save failed");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Saved Wi-Fi credentials for SSID: %s", ssid);
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    if (is_lang_en(lang)) {
        httpd_resp_sendstr(
            req,
            "<html><body style='font-family:Segoe UI,sans-serif;padding:24px;'>"
            "<h2>Wi-Fi saved</h2>"
            "<p>The device is restarting now. Reconnect to the target Wi-Fi and then use the device normally.</p>"
            "</body></html>");
    } else {
        httpd_resp_sendstr(
            req,
            "<html><body style='font-family:Segoe UI,PingFang SC,sans-serif;padding:24px;'>"
            "<h2>Wi-Fi 已保存</h2>"
            "<p>设备正在重启，请切换回目标 Wi-Fi，随后即可正常使用设备。</p>"
            "</body></html>");
    }

    xTaskCreate(restart_after_delay_task, "wifi_restart", 2048, NULL, 3, NULL);
    return ESP_OK;
}

static esp_err_t camera_provision_post_handler(httpd_req_t *req) {
    if (req->content_len <= 0 || req->content_len >= 256) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid payload");
        return ESP_FAIL;
    }

    char body[256] = {0};
    const int received = httpd_req_recv(req, body, req->content_len);
    if (received <= 0) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "read failed");
        return ESP_FAIL;
    }
    body[received] = '\0';

    char ssid[33] = {0};
    char password[65] = {0};
    char format_value[16] = {0};
    extract_form_field(body, "ssid", ssid, sizeof(ssid));
    extract_form_field(body, "password", password, sizeof(password));
    extract_form_field(body, "format", format_value, sizeof(format_value));

    if (ssid[0] == '\0') {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "ssid required");
        return ESP_FAIL;
    }
    if (password[0] != '\0' && strlen(password) < 8) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "password too short");
        return ESP_FAIL;
    }

    camera_i2c_provision_format_t format = CAMERA_I2C_PROVISION_WIFI;
    if (format_value[0] != '\0' && !parse_camera_provision_format(format_value, &format)) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid camera provision format");
        return ESP_FAIL;
    }

    CameraI2cStatus camera = {};
    esp_err_t err = camera_i2c_client_provision_wifi_and_read(ssid, password, format, &camera);
    if (err != ESP_OK && err != ESP_ERR_TIMEOUT && !camera.reachable) {
        ESP_LOGW(TAG, "Camera I2C provisioning failed: %s", esp_err_to_name(err));
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, esp_err_to_name(err));
        return ESP_FAIL;
    }

    char response_json[1024] = {};
    int offset = 0;
    bool ok = append_text(response_json, sizeof(response_json), &offset, "{\"ok\":true,\"camera\":");
    ok = ok && append_camera_status_json(response_json, sizeof(response_json), &offset, &camera);
    ok = ok && append_text(response_json, sizeof(response_json), &offset, "}");
    if (!ok) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "camera payload too large");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    return httpd_resp_send(req, response_json, HTTPD_RESP_USE_STRLEN);
}

static esp_err_t runtime_config_post_handler(httpd_req_t *req) {
    if (req->content_len <= 0 || req->content_len >= 256) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid payload");
        return ESP_FAIL;
    }

    char body[256] = {0};
    const int received = httpd_req_recv(req, body, req->content_len);
    if (received <= 0) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "read failed");
        return ESP_FAIL;
    }
    body[received] = '\0';

    char comm_mode_value[16] = {0};
    char agent_ip[16] = {0};
    char agent_port_value[8] = {0};
    extract_form_field(body, "comm_mode", comm_mode_value, sizeof(comm_mode_value));
    extract_form_field(body, "microros_agent_ip", agent_ip, sizeof(agent_ip));
    extract_form_field(body, "microros_agent_port", agent_port_value, sizeof(agent_port_value));

    WifiRuntimeConfig config = {};
    if (!parse_comm_mode(comm_mode_value, &config.comm_mode)) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid comm mode");
        return ESP_FAIL;
    }
    if (!is_valid_ipv4_address(agent_ip)) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid micro-ROS agent IP");
        return ESP_FAIL;
    }

    char *port_end = nullptr;
    const long port = strtol(agent_port_value, &port_end, 10);
    if (agent_port_value[0] == '\0' || port_end == agent_port_value ||
        *port_end != '\0' || port <= 0 || port > 65535) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid micro-ROS agent port");
        return ESP_FAIL;
    }

    strncpy(config.microros_agent_ip, agent_ip, sizeof(config.microros_agent_ip) - 1);
    config.microros_agent_ip[sizeof(config.microros_agent_ip) - 1] = '\0';
    config.microros_agent_port = static_cast<uint16_t>(port);

    esp_err_t err = wifi_save_runtime_config(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to save runtime config: %s", esp_err_to_name(err));
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "save failed");
        return ESP_FAIL;
    }

    system_globals().runtime.wifi_comm_mode = config.comm_mode;
    snprintf(system_globals().runtime.microros_agent_ip, sizeof(system_globals().runtime.microros_agent_ip), "%s",
             config.microros_agent_ip);
    system_globals().runtime.microros_agent_port = config.microros_agent_port;

    ESP_LOGI(TAG, "Saved runtime config: comm=%s, micro-ROS agent=%s:%u",
             SystemGlobals::WifiCommModeToRuntimeValue(system_globals().runtime.wifi_comm_mode),
             system_globals().runtime.microros_agent_ip,
             static_cast<unsigned>(system_globals().runtime.microros_agent_port));
    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"ok\":true,\"restart\":true}");
    xTaskCreate(restart_after_delay_task, "runtime_restart", 2048, NULL, 3, NULL);
    return ESP_OK;
}

static int find_dns_question_end(const uint8_t *packet, int packet_len) {
    int index = 12;
    while (index < packet_len) {
        const uint8_t label_len = packet[index++];
        if (label_len == 0) {
            break;
        }
        index += label_len;
    }

    if (index + 4 > packet_len) {
        return -1;
    }
    return index + 4;
}

static void captive_dns_task(void *pvParameters) {
    esp_netif_ip_info_t ap_ip_info = {};
    if (wifi_get_softap_ip_info(&ap_ip_info) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SoftAP IP info for captive DNS");
        vTaskDelete(NULL);
        return;
    }

    const uint32_t ap_ip = ap_ip_info.ip.addr;
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        ESP_LOGE(TAG, "Failed to create captive DNS socket");
        vTaskDelete(NULL);
        return;
    }

    struct sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(53);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(server_addr)) != 0) {
        ESP_LOGE(TAG, "Failed to bind captive DNS socket");
        close(sock);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Captive DNS started on UDP/53");

    uint8_t request[kDnsPacketMaxSize] = {0};
    uint8_t response[kDnsPacketMaxSize] = {0};

    while (true) {
        struct sockaddr_in client_addr = {};
        socklen_t client_len = sizeof(client_addr);
        const int recv_len = recvfrom(sock, request, sizeof(request), 0,
                                      reinterpret_cast<struct sockaddr *>(&client_addr), &client_len);
        if (recv_len < 12) {
            continue;
        }

        const int question_end = find_dns_question_end(request, recv_len);
        if (question_end <= 0 || question_end > recv_len) {
            continue;
        }

        memcpy(response, request, question_end);
        response[2] = 0x81;
        response[3] = 0x80;
        response[4] = 0x00;
        response[5] = 0x01;
        response[8] = 0x00;
        response[9] = 0x00;
        response[10] = 0x00;
        response[11] = 0x00;

        const uint16_t query_type =
            static_cast<uint16_t>((request[question_end - 4] << 8) | request[question_end - 3]);
        const uint16_t query_class =
            static_cast<uint16_t>((request[question_end - 2] << 8) | request[question_end - 1]);

        int response_len = question_end;
        if (query_type == 0x0001 && query_class == 0x0001 &&
            question_end + 16 <= static_cast<int>(sizeof(response))) {
            response[6] = 0x00;
            response[7] = 0x01;

            response[response_len++] = 0xC0;
            response[response_len++] = 0x0C;
            response[response_len++] = 0x00;
            response[response_len++] = 0x01;
            response[response_len++] = 0x00;
            response[response_len++] = 0x01;
            response[response_len++] = 0x00;
            response[response_len++] = 0x00;
            response[response_len++] = 0x00;
            response[response_len++] = 0x3C;
            response[response_len++] = 0x00;
            response[response_len++] = 0x04;
            memcpy(response + response_len, &ap_ip, 4);
            response_len += 4;
        } else {
            response[6] = 0x00;
            response[7] = 0x00;
        }

        sendto(sock, response, response_len, 0,
               reinterpret_cast<struct sockaddr *>(&client_addr), client_len);
    }
}

void provision_portal_start(void) {
    if (s_http_buffer_mutex == nullptr) {
        s_http_buffer_mutex = xSemaphoreCreateMutex();
        if (s_http_buffer_mutex == nullptr) {
            ESP_LOGE(TAG, "Failed to create HTTP buffer mutex");
            return;
        }
    }

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 80;
    config.stack_size = 12288;
    config.max_uri_handlers = 13;
    config.uri_match_fn = httpd_uri_match_wildcard;

    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start provisioning HTTP server");
        return;
    }

    httpd_uri_t uri_root = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_get_handler,
        .user_ctx = NULL,
    };
    httpd_uri_t uri_scan = {
        .uri = "/api/scan",
        .method = HTTP_GET,
        .handler = scan_get_handler,
        .user_ctx = NULL,
    };
    httpd_uri_t uri_status = {
        .uri = "/api/status",
        .method = HTTP_GET,
        .handler = status_get_handler,
        .user_ctx = NULL,
    };
    httpd_uri_t uri_provision = {
        .uri = "/api/provision",
        .method = HTTP_POST,
        .handler = provision_post_handler,
        .user_ctx = NULL,
    };
    httpd_uri_t uri_runtime_config = {
        .uri = "/api/runtime-config",
        .method = HTTP_POST,
        .handler = runtime_config_post_handler,
        .user_ctx = NULL,
    };
    httpd_uri_t uri_camera_provision = {
        .uri = "/api/camera/provision",
        .method = HTTP_POST,
        .handler = camera_provision_post_handler,
        .user_ctx = NULL,
    };
    httpd_uri_t uri_captive_all = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = root_get_handler,
        .user_ctx = NULL,
    };

    httpd_register_uri_handler(server, &uri_root);
    httpd_register_uri_handler(server, &uri_scan);
    httpd_register_uri_handler(server, &uri_status);
    httpd_register_uri_handler(server, &uri_provision);
    httpd_register_uri_handler(server, &uri_runtime_config);
    httpd_register_uri_handler(server, &uri_camera_provision);
    httpd_register_uri_handler(server, &uri_captive_all);

    xTaskCreate(captive_dns_task, "captive_dns", 4096, NULL, 3, NULL);

    ESP_LOGI(TAG, "Provisioning server started on port 80");
}
