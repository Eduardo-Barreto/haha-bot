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
    communication_init();

    for (;;) {
        line_sensors_update_reading();

        char* message = array_to_string(line_sensors_get_readings(), 8);
        strcat(message, "\n");
        communication_send_message(message);
    }

    return 0;
}
