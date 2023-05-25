#include "encoders.h"
#include "gpio.h"
#include <stdint.h>

#define LEFT_ENCODER1 GPIO_PIN_12
#define LEFT_ENCODER2 GPIO_PIN_13

#define RIGHT_ENCODER1 GPIO_PIN_14
#define RIGHT_ENCODER2 GPIO_PIN_15

#define ENCODER_PORT GPIOB

volatile uint32_t motor_a_position;
volatile uint32_t motor_b_position;

void encoders_init(void) {
    (void) 0;
}

void encoders_reset_position_a(void) {
    motor_a_position = 0;
}

uint32_t encoders_get_position_a(void) {
    return motor_a_position;
}

void encoders_reset_position_b(void) {
    motor_b_position = 0;
}

uint32_t encoders_get_position_b(void) {
    return motor_b_position;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == LEFT_ENCODER1) {
        if (HAL_GPIO_ReadPin(ENCODER_PORT, LEFT_ENCODER1) == HAL_GPIO_ReadPin(ENCODER_PORT, LEFT_ENCODER2)) {
            motor_a_position--;
        } else {
            motor_a_position++;
        }

        return;
    }

    if (GPIO_Pin == LEFT_ENCODER2) {
        if (HAL_GPIO_ReadPin(ENCODER_PORT, LEFT_ENCODER1) == HAL_GPIO_ReadPin(ENCODER_PORT, LEFT_ENCODER2)) {
            motor_a_position++;
        } else {
            motor_a_position--;
        }

        return;
    }

    if (GPIO_Pin == RIGHT_ENCODER1) {
        if (HAL_GPIO_ReadPin(ENCODER_PORT, RIGHT_ENCODER1) == HAL_GPIO_ReadPin(ENCODER_PORT, RIGHT_ENCODER2)) {
            motor_b_position--;
        } else {
            motor_b_position++;
        }

        return;
    }

    if (GPIO_Pin == RIGHT_ENCODER2) {
        if (HAL_GPIO_ReadPin(ENCODER_PORT, RIGHT_ENCODER1) == HAL_GPIO_ReadPin(ENCODER_PORT, RIGHT_ENCODER2)) {
            motor_b_position++;
        } else {
            motor_b_position--;
        }
    }
}
