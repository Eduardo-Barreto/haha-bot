#ifndef __LINE_SENSORS_H__
#define __LINE_SENSORS_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct sensors_calibration {
    uint32_t min;
    uint32_t max;
} sensors_calibration_t;

#define LINE_SENSORS_NUMBER_OF_SENSORS 8

sensors_calibration_t line_sensors_calibration[LINE_SENSORS_NUMBER_OF_SENSORS] = {
    {0, 4095},
    {0, 4095},
    {0, 4095},
    {0, 4095},
    {0, 4095},
    {0, 4095},
    {0, 4095},
    {0, 4095}
};

void line_sensors_init();

bool line_sensor_is_on_line(uint8_t sensor_idx);

float line_sensor_get_reading(uint8_t sensor_idx);

void line_sensors_update_reading();

float line_sensors_get_position();

#endif // __LINE_SENSORS_H__
