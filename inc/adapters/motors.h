#ifndef __MOTORS_H__
#define __MOTORS_H__

#include <stdint.h>

#include "gpio.h"

void motors_init(void);

void motors_set_speed(int8_t left_speed, int8_t right_speed);

void motors_stop(void);

void motors_break(void);

void motors_die(void);

#endif
