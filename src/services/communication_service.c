#include "communication_service.h"
#include "usart.h"

#define MAX_BUFFER_SIZE 256

volatile char reading_command[MAX_BUFFER_SIZE];
volatile char last_command[MAX_BUFFER_SIZE] = "0\r\n";
static uint8_t rx_buffer[MAX_BUFFER_SIZE];
volatile char rx_data;
volatile uint8_t rx_index = 0;
volatile bool rx_line_complete = false;

void communication_init(void) {
    MX_DMA_Init();
    MX_USART1_UART_Init();
    HAL_UART_Receive_DMA(&huart1, rx_buffer, MAX_BUFFER_SIZE);
    rx_line_complete = false;
}

bool communication_line_available() {
    return rx_line_complete;
}

char* communication_get_last_line() {
    if (rx_line_complete) {
        rx_line_complete = false;
        return last_command;
    }

    return NULL;
}

bool communication_is_command(char* command) {
    char* last_line = communication_get_last_line();

    if (last_line == NULL) {
        return false;
    }

    return strstr(last_line, command) != NULL;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance != USART1) {
        return;
    }

    rx_data = rx_buffer[rx_index];

    rx_index = (rx_index + 1) % MAX_BUFFER_SIZE;

    if ((rx_data == '\r') || (rx_data == '\n')) {
        rx_line_complete = true;

        strcpy(last_command, reading_command);
        reading_command[0] = '\0';
        rx_line_complete = true;
        return;
    }

    strcat(reading_command, rx_data);
}

void communication_send_message(char* message) {
    HAL_UART_Transmit_DMA(&huart1, (uint8_t*) message, strlen(message));
}
