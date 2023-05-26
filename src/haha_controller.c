#include "encoders.h"
#include "line_sensors.h"
#include "mcu.h"
#include "motors.h"
#include "communication_service.h"
#include "calibration_service.h"
#include "follow_line_service.h"
#include "haha_controller.h"
#include <stdio.h>
#include <stdint.h>

typedef enum haha_controller_state {
    IDLE,
    CALIBRATE,
    PRINT_CALIBRATION,
    PRINT_LINE_SENSORS,
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
    communication_send_message("Ebaaaaa!\n");
}

void haha_controller_loop(void) {
    if (communication_is_command("stop")) {
        current_state = STOP;
        communication_send_message("STOP\n");
    }

    switch (current_state) {
        case IDLE:

            if (communication_is_command("calibrate")) {
                current_state = CALIBRATE;
                communication_send_message("CALIBRATE\n");
            } else if (communication_is_command("follow_line")) {
                current_state = FOLlOW_LINE;
                communication_send_message("FOLlOW_LINE\n");
            } else if (communication_is_command("print_calibration")) {
                current_state = PRINT_CALIBRATION;
                communication_send_message("PRINT_CALIBRATION\n");
            } else if (communication_is_command("print_line_sensors")) {
                current_state = PRINT_LINE_SENSORS;
                communication_send_message("PRINT_LINE_SENSORS\n");
            }

            break;

        case CALIBRATE:

            calibrate_all_sensors();
            current_state = IDLE;
            communication_send_message("IDLE\n");

            break;

        case PRINT_CALIBRATION:
            ;

            for (uint8_t i = 0; i < 8; i++) {
                uint16_t min_reading = line_sensors_calibration[i].min;
                uint16_t max_reading = line_sensors_calibration[i].max;

                uint8_t* message[30];
                sprintf(message, "%d\t%d\t", min_reading, max_reading);
                communication_send_message(message);
            }

            communication_send_message("\nIDLE\n");

            current_state = IDLE;
            break;

        case PRINT_LINE_SENSORS:
            ;

            line_sensors_update_reading();
            uint32_t* readings = line_sensors_get_readings();

            // pra cada sensor printa o valor
            for (uint8_t i = 0; i < 8; i++) {
                uint8_t* message[30];
                sprintf(message, "%d\t", readings[i]);
                communication_send_message(message);
            }

            communication_send_message("\t");

            // printa a posicao da linha
            line_position = line_sensors_get_position();
            uint8_t* message[30];
            sprintf(message, "p: %d\n", (int) (line_position * 10));
            communication_send_message(message);
            break;

        case FOLlOW_LINE:
            line_sensors_update_reading();
            line_position = line_sensors_get_position();

            follow_line(line_position);

            if (communication_is_command("stop")) {
                current_state = STOP;
                communication_send_message("STOP\n");
            }

            break;

        case STOP:
            motors_set_speed(0.0f, 0.0f);
            current_state = IDLE;
            communication_send_message("IDLE\n");

            break;
    }
}
