#pragma once
// Keep format checking enabled in host tests without producing firmware logs.
#include <cstdio>
#define ESP_LOGW(tag, fmt, ...) do { (void)(tag); if (false) std::printf(fmt, ##__VA_ARGS__); } while (0)
#define ESP_LOGI ESP_LOGW
