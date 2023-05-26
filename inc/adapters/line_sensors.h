#ifndef __LINE_SENSORS_H__
#define __LINE_SENSORS_H__

#include <stdbool.h>
#include <stdint.h>

#define LINE_SENSORS_NUMBER_OF_SENSORS 8

typedef struct sensors_calibration {
    uint32_t min;
    uint32_t max;
} sensors_calibration_t;

void line_sensors_init();

bool line_sensor_is_on_line(uint8_t sensor_idx);

uint32_t* line_sensors_get_raw_readings();

uint32_t* line_sensors_get_readings();

void line_sensors_update_reading();

float line_sensors_get_position();

#endif // __LINE_SENSORS_H__
