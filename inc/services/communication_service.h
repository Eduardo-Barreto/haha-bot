#ifndef __COMMUNICATION_SERVICE_H__
#define __COMMUNICATION_SERVICE_H__

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

void communication_init(void);

bool communication_line_available();

char* communication_get_last_line();

bool communication_is_command(char* command);

void communication_send_message(char* message);

#endif
