#pragma once
#include <cstddef>
#include <cstdint>
#include "gpio.h"
using uart_port_t = int;
constexpr int UART_DATA_8_BITS=8, UART_PARITY_DISABLE=0, UART_STOP_BITS_1=1;
constexpr int UART_HW_FLOWCTRL_DISABLE=0, UART_SCLK_DEFAULT=0, UART_PIN_NO_CHANGE=-1;
struct uart_config_t { int baud_rate, data_bits, parity, stop_bits, flow_ctrl, source_clk; };
int uart_driver_install(uart_port_t, int, int, int, void*, int);
int uart_param_config(uart_port_t, const uart_config_t*);
int uart_set_pin(uart_port_t, int, int, int, int);
int uart_get_buffered_data_len(uart_port_t, size_t*);
int uart_read_bytes(uart_port_t, void*, uint32_t, int);
