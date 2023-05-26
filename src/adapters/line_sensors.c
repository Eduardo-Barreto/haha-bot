#include "adc.h"
#include "utils.h"
#include "gpio.h"
#include "communication_service.h"
#include "line_sensors.h"

#define LINE_SENSOR_THRESHOLD 20

#define LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR 50

#define LINE_SENSORS_ADC_HANDLE (hadc1)
#define LINE_SENSORS_ADC_BUFFER_SIZE (LINE_SENSORS_NUMBER_OF_SENSORS * LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR)

#define LINE_SENSORS_ON_PORT GPIOB
#define LINE_SENSORS_ON_PIN GPIO_PIN_2

const float SENSORS_WEIGHT[] = {4.0, 3.0, 2.0, 0, 0, -2.0, -3.0, -4.0};

static uint32_t m_adc_reading[LINE_SENSORS_NUMBER_OF_SENSORS] = {0, 0, 0, 0, 0, 0, 0, 0};
static uint32_t m_adc_raw_reading[LINE_SENSORS_NUMBER_OF_SENSORS] = {0, 0, 0, 0, 0, 0, 0, 0};
static uint32_t m_adc_buffer[LINE_SENSORS_ADC_BUFFER_SIZE] = {0};
static volatile bool m_finished_reading = false;

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

void line_sensors_init() {
    HAL_GPIO_WritePin(LINE_SENSORS_ON_PORT, LINE_SENSORS_ON_PIN, 1);
    MX_DMA_Init();
    MX_ADC1_Init();
    HAL_ADC_Start_DMA(&LINE_SENSORS_ADC_HANDLE, m_adc_buffer, LINE_SENSORS_ADC_BUFFER_SIZE);
}

bool line_sensor_is_on_line(uint8_t sensor_idx) {
    return m_adc_reading[sensor_idx] < LINE_SENSOR_THRESHOLD;
}

uint32_t* line_sensors_get_readings() {
    return m_adc_reading;
}

uint32_t* line_sensors_get_raw_readings() {
    return m_adc_raw_reading;
}

void line_sensors_update_reading() {
    if (!m_finished_reading) {
        return;
    }

    HAL_ADC_Stop_DMA(&LINE_SENSORS_ADC_HANDLE);

    // Zera todas as leituras
    for (uint8_t sensor = 0; sensor < LINE_SENSORS_NUMBER_OF_SENSORS; sensor++) {
        m_adc_raw_reading[sensor] = 0;
    }

    // Calcula a média das leituras
    for (uint8_t sensor = 0; sensor < LINE_SENSORS_NUMBER_OF_SENSORS; sensor++) {
        for (uint8_t read = 0; read < LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR; read++) {
            m_adc_raw_reading[sensor] += m_adc_buffer[sensor + read * LINE_SENSORS_NUMBER_OF_SENSORS];
        }

        m_adc_raw_reading[sensor] /= LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR;

        m_adc_reading[sensor] = map(
            m_adc_raw_reading[sensor],
            line_sensors_calibration[sensor].min,
            line_sensors_calibration[sensor].max,
            0,
            100
            );

        if (m_adc_reading[sensor] > 100) {
            m_adc_reading[sensor] = 0;
        }
    }

    // Reinicia o DMA
    m_finished_reading = false;
    HAL_ADC_Start_DMA(&LINE_SENSORS_ADC_HANDLE, m_adc_buffer, LINE_SENSORS_ADC_BUFFER_SIZE);
}

float line_sensors_get_position() {
    float position = 0;
    uint8_t black_sensors_count = 0;

    for (uint8_t sensor = 0; sensor < LINE_SENSORS_NUMBER_OF_SENSORS; sensor++) {
        if (!line_sensor_is_on_line(sensor)) {
            continue;
        }

        position += SENSORS_WEIGHT[sensor];
        black_sensors_count++;
    }

    if (black_sensors_count > 0) {
        position /= (float) black_sensors_count;
    }

    return position;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == LINE_SENSORS_ADC_HANDLE.Instance) {
        m_finished_reading = true;
    }
}
