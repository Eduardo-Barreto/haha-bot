#include <stdbool.h>
#include <stdint.h>
#include "test_core.h"
#include "mcu.h"
#include "motors.h"
#include "communication_service.h"
#include "encoders.h"

#define SPEED 50
#define SLEEP_TIME_MS 2000U

const int8_t SPEEDS[8][2] = {
    {SPEED, SPEED},
    {SPEED, 0},
    {0, SPEED},
    {0, 0},
    {-SPEED, -SPEED},
    {-SPEED, 0},
    {0, -SPEED},
    {0, 0}
};

int main(void) {
    test_core_init();
    motors_init();
    communication_init();

    for (;;) {
        for (uint8_t i = 0; i < 8; i++) {
            motors_set_speed(SPEEDS[i][0], SPEEDS[i][1]);
            uint8_t* message[30];
            sprintf(message, "speed: %d, %d | Left: %d Right: %d\n", SPEEDS[i][0], SPEEDS[i][1],
                    encoders_get_position_a(), encoders_get_position_b());
            communication_send_message(message);
            mcu_sleep(SLEEP_TIME_MS);
        }
    }

    return 0;
}
