#pragma once

#include <stdint.h>
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/uart.h"
#include "hal/adc_types.h"

namespace leap_config {
namespace board {

static constexpr gpio_num_t kMotorLeftIn1 = GPIO_NUM_46;
static constexpr gpio_num_t kMotorLeftIn2 = GPIO_NUM_9;
static constexpr gpio_num_t kMotorRightIn1 = GPIO_NUM_16;
static constexpr gpio_num_t kMotorRightIn2 = GPIO_NUM_15;

static constexpr gpio_num_t kEncoderLeftA = GPIO_NUM_10;
static constexpr gpio_num_t kEncoderLeftB = GPIO_NUM_11;
static constexpr gpio_num_t kEncoderRightA = GPIO_NUM_17;
static constexpr gpio_num_t kEncoderRightB = GPIO_NUM_18;

static constexpr gpio_num_t kUltrasonicTrigPin = GPIO_NUM_21;
static constexpr gpio_num_t kUltrasonicEchoPin = GPIO_NUM_47;
static constexpr gpio_num_t kStatusLedPin = GPIO_NUM_14;
static constexpr gpio_num_t kServoPin = GPIO_NUM_48;
static constexpr adc_unit_t kBatteryAdcUnit = ADC_UNIT_1;
static constexpr adc_channel_t kBatteryAdcChannel = ADC_CHANNEL_2; // GPIO3 on ESP32-S3.

// GPIO0/BOOT is a strapping/download pin. Using it as a runtime button is risky,
// but it is enabled here intentionally for the BOOT long-press recovery action.
static constexpr gpio_num_t kIo0ButtonPin = GPIO_NUM_0;

static constexpr i2c_port_t kImuI2cPort = I2C_NUM_0;
static constexpr gpio_num_t kImuSdaPin = GPIO_NUM_12;
static constexpr gpio_num_t kImuSclPin = GPIO_NUM_13;
static constexpr gpio_num_t kLidarTxPin = static_cast<gpio_num_t>(UART_PIN_NO_CHANGE);
static constexpr gpio_num_t kLidarRxPin = GPIO_NUM_41;
static constexpr uint8_t kGamepadI2cAddress = 0x50;
static constexpr uint32_t kBatterySamplePeriodMs = 500;
static constexpr uint32_t kBootWifiResetLongPressMs = 3000;
static constexpr uint32_t kTemperatureSamplePeriodMs = 1000;

}  // namespace board
}  // namespace leap_config
