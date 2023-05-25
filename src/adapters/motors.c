#include <stdint.h>
#include "motors.h"
#include "utils.h"
#include "tim.h"
#include "gpio.h"

#define MOTOR_TIM_HANDLE (htim2)

#define RIGHT_MOTOR TIM_CHANNEL_1
#define LEFT_MOTOR TIM_CHANNEL_2

#define MOTORS_PORT GPIOB

#define RIGHT_FORWARD_PIN GPIO_PIN_8
#define RIGHT_BACKWARD_PIN GPIO_PIN_7
#define LEFT_FORWARD_PIN GPIO_PIN_5
#define LEFT_BACKWARD_PIN GPIO_PIN_4

void motors_init() {
    MX_TIM2_Init();

    HAL_TIM_PWM_Start(&MOTOR_TIM_HANDLE, LEFT_MOTOR);
    HAL_TIM_PWM_Start(&MOTOR_TIM_HANDLE, RIGHT_MOTOR);
}

void motors_set_speed(int8_t left_speed, int8_t right_speed) {
    HAL_GPIO_WritePin(MOTORS_PORT, LEFT_FORWARD_PIN, (left_speed >= 0));
    HAL_GPIO_WritePin(MOTORS_PORT, LEFT_BACKWARD_PIN, (left_speed < 0));

    HAL_GPIO_WritePin(MOTORS_PORT, RIGHT_FORWARD_PIN, (right_speed >= 0));
    HAL_GPIO_WritePin(MOTORS_PORT, RIGHT_BACKWARD_PIN, (right_speed < 0));

    TIM2->CCR1 = abs(right_speed);
    TIM2->CCR2 = abs(left_speed);
}

void motors_stop() {
    motors_set_speed(0, 0);
}

void motors_break() {
    motors_stop();
    HAL_GPIO_WritePin(MOTORS_PORT, LEFT_FORWARD_PIN, 1);
    HAL_GPIO_WritePin(MOTORS_PORT, LEFT_BACKWARD_PIN, 1);
    HAL_GPIO_WritePin(MOTORS_PORT, LEFT_FORWARD_PIN, 1);
    HAL_GPIO_WritePin(MOTORS_PORT, LEFT_BACKWARD_PIN, 1);
}

void motors_die() {
    motors_break();

    for (;;)
        ;
}
