#pragma once

#include "esp_err.h"
#include "msg/pid_msg.h"

esp_err_t pid_load_speed_config(PidMsg *config);
esp_err_t pid_save_speed_config(const PidMsg *config);
