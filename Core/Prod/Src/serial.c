#include "serial.h"

uint8_t lidarReading[2];

int serial_send(char *ptr, int len) {
	HAL_UART_Transmit(&huart6, (uint8_t *) ptr, len, HAL_MAX_DELAY);
	return len;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	if(huart->Instance == USART6){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		printf("%d, %d\r\n", lidarReading[0], lidarReading[1]);

		HAL_UART_Receive_IT(&huart6, lidarReading, 2);
	}
}
