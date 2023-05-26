#include "communication_service.h"
#include "usart.h"

#define MAX_BUFFER_SIZE 256

volatile uint8_t reading_command[MAX_BUFFER_SIZE];
volatile uint8_t last_command[MAX_BUFFER_SIZE] = { 0 };
static uint8_t rx_buffer[MAX_BUFFER_SIZE];
volatile uint8_t rx_index = 0;
volatile bool rx_line_complete = false;

void communication_init(void) {
    MX_USART1_UART_Init();
    HAL_UART_Receive_IT(&huart1, &rx_buffer[rx_index], 1);
    rx_line_complete = false;
}

bool communication_line_available() {
    return rx_line_complete;
}

uint8_t* communication_get_last_line() {
    if (rx_line_complete) {
        rx_line_complete = false;
        return last_command;
    }

    return NULL;
}

bool communication_is_command(uint8_t* command) {
    uint8_t* last_line = communication_get_last_line();

    if (last_line == NULL) {
        return false;
    }

    return strstr((char*) last_line, (char*) command) != NULL;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance != USART1) {
        return;
    }

    reading_command[rx_index] = rx_buffer[rx_index];

    if (reading_command[rx_index] == '\n') {
        reading_command[rx_index + 1] = '\0';
        memset(last_command, 0, sizeof(last_command));
        memcpy(last_command, &reading_command[rx_index - rx_index], rx_index + 1);
        rx_line_complete = true;
        rx_index = 0;

        memset(reading_command, 0, sizeof(reading_command));
        memset(rx_buffer, 0, sizeof(rx_buffer));
    } else {
        rx_index = (rx_index + 1) % MAX_BUFFER_SIZE;
    }

    HAL_UART_Receive_IT(&huart1, &rx_buffer[rx_index], 1);
}

void communication_send_message(uint8_t* message) {
    uint16_t size = strlen((char*) message);
    HAL_UART_Transmit(&huart1, message, size, 1000);
}
