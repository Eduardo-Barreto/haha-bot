#ifndef __calibration_service_H__
#define __calibration_service_H__

#include <stdint.h>
#include <stdbool.h>
#include "line_sensors.h"

extern sensors_calibration_t line_sensors_calibration[LINE_SENSORS_NUMBER_OF_SENSORS];

void calibration_service_init(void);

void calibrate_all_sensors();

#endif
