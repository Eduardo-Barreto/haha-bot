#include "calibration_service.h"
#include "mcu.h"
#include "motors.h"
#include "utils.h"
#include <stdio.h>

#define TIME_TO_CALIBRATE 2000

void calibration_service_init(void) {
    (void) 0;
}

void calibrate_all_sensors() {
    for (uint8_t sensor_idx = 0; sensor_idx < LINE_SENSORS_NUMBER_OF_SENSORS; sensor_idx++) {
        line_sensors_calibration[sensor_idx].min = 4095;
        line_sensors_calibration[sensor_idx].max = 0;
    }

    line_sensors_update_reading();
    uint32_t start_time = HAL_GetTick();

    while (HAL_GetTick() - start_time < TIME_TO_CALIBRATE) {
        line_sensors_update_reading();

        uint32_t* readings = line_sensors_get_raw_readings();

        for (uint8_t sensor_idx = 0; sensor_idx < LINE_SENSORS_NUMBER_OF_SENSORS; sensor_idx++) {
            uint32_t sensor_reading = readings[sensor_idx];

            uint8_t* message[30];
            sprintf(message, "%d\t", sensor_reading);
            communication_send_message(message);

            line_sensors_calibration[sensor_idx].min = min(
                line_sensors_calibration[sensor_idx].min, sensor_reading);
            line_sensors_calibration[sensor_idx].max = max(line_sensors_calibration[sensor_idx].max, sensor_reading);
        }

        communication_send_message("\n");
    }

    for (uint8_t sensor_idx = 0; sensor_idx < LINE_SENSORS_NUMBER_OF_SENSORS; sensor_idx++) {
        uint32_t min_calibration = line_sensors_calibration[sensor_idx].min;
        uint32_t max_calibration = line_sensors_calibration[sensor_idx].max;

        char* message[40];
        sprintf(message, "sensor %d: min = %d, max = %d\n", sensor_idx, min_calibration, max_calibration);

        communication_send_message(message);
    }
}
