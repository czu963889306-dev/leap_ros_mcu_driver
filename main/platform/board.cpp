#include "board.h"
#include "board_config.h"

#include "esp_log.h"

static const char *TAG = "BOARD_INIT";

namespace board_cfg = leap_config::board;

// ================= 对象实例化 =================
Lsm6ds3Imu imu(board_cfg::kImuI2cPort, board_cfg::kImuSdaPin, board_cfg::kImuSclPin);

At8236Motor motor_left(board_cfg::kMotorLeftIn1, board_cfg::kMotorLeftIn2);
At8236Motor motor_right(board_cfg::kMotorRightIn1, board_cfg::kMotorRightIn2);

QuadratureEncoder encoder_left(board_cfg::kEncoderLeftA, board_cfg::kEncoderLeftB);
QuadratureEncoder encoder_right(board_cfg::kEncoderRightA, board_cfg::kEncoderRightB);

MotionController robot(motor_left, motor_right, encoder_left, encoder_right);
UltrasonicSensor ultrasonic(board_cfg::kUltrasonicTrigPin, board_cfg::kUltrasonicEchoPin);
StatusLed status_led(board_cfg::kStatusLedPin);
ButtonDriver io0_button(board_cfg::kIo0ButtonPin, true);
ServoDriver my_servo(board_cfg::kServoPin);
BatteryAdc battery_adc(board_cfg::kBatteryAdcUnit, board_cfg::kBatteryAdcChannel);

// ================= 统一初始化逻辑 =================
void board_init(void) {
    ESP_LOGI(TAG, "Initializing two-wheel differential hardware...");

    motor_left.Init();
    encoder_left.Init();
    motor_right.Init();
    encoder_right.Init();

    ultrasonic.Init();
    status_led.Init();
    io0_button.Init();
    ESP_LOGW(TAG, "BOOT/IO0 is used as a runtime communication-mode button; holding it during reset may enter download mode.");
    my_servo.Init();

    if (imu.Init()) {
        ESP_LOGI(TAG, "IMU (LSM6DS3) initialized.");
    } else {
        ESP_LOGE(TAG, "IMU initialization failed.");
    }

    ESP_LOGI(TAG, "Two-wheel differential board ready.");
}
