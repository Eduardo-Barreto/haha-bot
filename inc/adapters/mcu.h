#ifndef __MCU_H__
#define __MCU_H__

#include <stdint.h>

void mcu_init(void);

void SystemClock_Config(void);

void mcu_sleep(uint32_t ms);

void led_toggle(void);

#endif
