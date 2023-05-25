#ifndef __ENCODERS_H__
#define __ENCODERS_H__

#include <stdint.h>
#include <stdbool.h>

void encoders_init(void);

void encoders_reset_position_a(void);

uint32_t encoders_get_position_a(void);

void encoders_reset_position_b(void);

uint32_t encoders_get_position_b(void);

#endif
