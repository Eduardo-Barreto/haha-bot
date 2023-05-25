#include "calibration_service.h"
#include "mcu.h"
#include "line_sensors.h"
#include "motors.h"
#include "utils.h"

#define TIME_TO_CALIBRATE 1000

void calibration_service_init(void) {
    (void) 0;
}

void calibrate_all_sensors() {
    for (uint8_t sensor_idx = 0; sensor_idx < LINE_SENSORS_NUMBER_OF_SENSORS; sensor_idx++) {
        line_sensors_calibration[sensor_idx].min = 4095;
        line_sensors_calibration[sensor_idx].max = 0;
    }

    motors_set_speed(50, 50);
    uint32_t start_time = HAL_GetTick();

    while (HAL_GetTick() - start_time < TIME_TO_CALIBRATE) {
        line_sensors_update_reading();

        for (uint8_t sensor_idx = 0; sensor_idx < LINE_SENSORS_NUMBER_OF_SENSORS; sensor_idx++) {
            uint32_t sensor_reading = line_sensor_get_reading(sensor_idx);

            line_sensors_calibration[sensor_idx].min = min(line_sensors_calibration[sensor_idx].min, sensor_reading);
            line_sensors_calibration[sensor_idx].max = max(line_sensors_calibration[sensor_idx].max, sensor_reading);
        }
    }

    motors_set_speed(0, 0);
    mcu_sleep(350);

    motors_set_speed(-50, -50);
    start_time = HAL_GetTick();

    while (HAL_GetTick() - start_time < TIME_TO_CALIBRATE) {
        line_sensors_update_reading();

        for (uint8_t sensor_idx = 0; sensor_idx < LINE_SENSORS_NUMBER_OF_SENSORS; sensor_idx++) {
            uint32_t sensor_reading = line_sensor_get_reading(sensor_idx);

            line_sensors_calibration[sensor_idx].min = min(line_sensors_calibration[sensor_idx].min, sensor_reading);
            line_sensors_calibration[sensor_idx].max = max(line_sensors_calibration[sensor_idx].max, sensor_reading);
        }
    }

    motors_set_speed(0, 0);
    mcu_sleep(350);
}
