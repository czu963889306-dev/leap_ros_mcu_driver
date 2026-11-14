#pragma once
#include <cassert>
#define ESP_ERROR_CHECK(expr) assert((expr) == 0)
#define ESP_LOGI(tag, ...) do { (void)(tag); } while (0)
