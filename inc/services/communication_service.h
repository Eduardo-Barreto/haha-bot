#ifndef __COMMUNICATION_SERVICE_H__
#define __COMMUNICATION_SERVICE_H__

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

void communication_init(void);

bool communication_line_available();

uint8_t* communication_get_last_line();

bool communication_is_command(uint8_t* command);

void communication_send_message(uint8_t* message);

#endif
