#include "test_core.h"
#include "mcu.h"
#include "communication_service.h"

int main(void) {
    test_core_init();
    led_toggle();
    communication_init();

    communication_send_message("Hello, world!\n");

    for (;;) {
        led_toggle();
        communication_send_message("toggle\n");
        mcu_sleep(500);
    }

    return 0;
}
