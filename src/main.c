
#include "haha_controller.h"

int main(void) {
    haha_controller_init();

    for (;;) {
        haha_controller_loop();
    }
}
