#include <stdbool.h>
#include <stdint.h>

#include "test_core.h"
#include "mcu.h"
#include "motors.h"
#include "communication_service.h"

int main(void) {
    test_core_init();
    motors_init();
    motors_stop();
    communication_init();
    led_toggle();
    communication_send_message("Hello, world!\n");

    for (;;) {
        communication_send_message(communication_get_last_line());

        /* if (!communication_line_available()) {
         *  continue;
         *  communication_send_message("not Available\n");
         * }
         *
         * communication_send_message("Available\n");
         *
         * communication_send_message(communication_get_last_line()); */
    }

    return 0;
}
