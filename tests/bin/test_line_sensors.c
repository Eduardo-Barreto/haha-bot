#include <stdbool.h>
#include <stdint.h>

#include "test_core.h"
#include "mcu.h"
#include "line_sensors.h"
#include "communication_service.h"

char* array_to_string(uint32_t* array, uint8_t size) {
    char* string = "";

    for (uint8_t i = 0; i < size; i++) {
        char* temp = "";
        sprintf(temp, "%d\t", array[i]);
        strcat(string, temp);
    }

    return string;
}

int main(void) {
    test_core_init();
    motors_init();
    line_sensors_init();
    communication_init();
    communication_send_message("Hello, world!\n");

    for (;;) {
        line_sensors_update_reading();

        /* uint32_t* message[30];
         * sprintf(message, "pos: %.2f\n", line_sensors_get_position());
         * communication_send_message(message); */

        uint32_t* readings = line_sensors_get_readings();

        // pra cada sensor printa o valor
        for (uint8_t i = 0; i < 8; i++) {
            uint32_t* message[30];
            sprintf(message, "%d\t", readings[i]);
            communication_send_message(message);
        }

        communication_send_message("\n");
    }

    return 0;
}
