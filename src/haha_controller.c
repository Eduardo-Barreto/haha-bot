#include "encoders.h"
#include "line_sensors.h"
#include "mcu.h"
#include "motors.h"
#include "communication_service.h"
#include "calibration_service.h"
#include "follow_line_service.h"
#include "haha_controller.h"

typedef enum haha_controller_state {
    IDLE,
    CALIBRATE,
    FOLlOW_LINE,
    STOP,
} haha_controller_state_t;

static haha_controller_state_t current_state = IDLE;
static float line_position = 0.0f;

void haha_controller_init(void) {
    mcu_init();
    line_sensors_init();
    motors_init();
    encoders_init();
    communication_init();
}

void haha_controller_loop(void) {
    switch (current_state) {
        case IDLE:

            if (communication_is_command("calibrate")) {
                current_state = CALIBRATE;
            } else if (communication_is_command("follow_line")) {
                current_state = FOLlOW_LINE;
            }

            break;

        case CALIBRATE:

            calibrate_all_sensors();
            current_state = IDLE;

            break;

        case FOLlOW_LINE:

            line_position = line_sensors_get_position();

            follow_line(line_position);

            if (communication_is_command("stop")) {
                current_state = STOP;
            }

            break;

        case STOP:
            motors_set_speed(0.0f, 0.0f);
            current_state = IDLE;

            break;
    }
}
