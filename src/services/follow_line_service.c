#include "follow_line_service.h"
#include "motors.h"

#define KP 10
#define KD 0.0f
#define KI 0.0f
#define SETPOINT 0
#define TARGET_SPEET 50

float last_error = 0.0f;
float integral = 0.0f;

void follow_line(float line_position) {
    float error = SETPOINT - line_position;
    integral = integral + error;
    float derivative = error - last_error;
    float output = KP * error + KI * integral + KD * derivative;

    motors_set_speed(TARGET_SPEET + output, TARGET_SPEET - output);
}
