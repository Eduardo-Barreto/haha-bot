#include "follow_line_service.h"
#include "motors.h"
#include "communication_service.h"
#include <stdio.h>

#define KP 50.0f
#define KD 0.0f
#define KI 0.001f
#define SETPOINT 0
#define TARGET_SPEET 90

float last_error = 0.0f;
float integral = 0.0f;

void follow_line(float line_position) {
    float error = SETPOINT - line_position;
    integral = integral + error;
    float derivative = error - last_error;
    float output = KP * error + KI * integral + KD * derivative;
    last_error = error;

    uint8_t* message[35];
    sprintf(message, "error: %d, output: %d\n", (int) (error), (int) (output));
    communication_send_message(message);

    motors_set_speed(TARGET_SPEET + output, TARGET_SPEET - output);
}
