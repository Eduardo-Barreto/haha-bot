#include <stdbool.h>
#include <stdint.h>

#include "test_core.h"
#include "mcu.h"
#include "motors.h"

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

    for (;;) {
        for (uint8_t i = 0; i < 8; i++) {
            motors_set_speed(SPEEDS[i][0], SPEEDS[i][1]);
            mcu_sleep_ms(SLEEP_TIME_MS);
        }
    }

    return 0;
}
