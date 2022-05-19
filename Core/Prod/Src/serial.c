#include "serial.h"

//int getUart

int serial_send(char *ptr, int len) {
	for (int i=0; i<len; i++) {
		HAL_UART_Transmit(&huart6, (uint8_t *) ptr++, 1, HAL_MAX_DELAY);
	}
	return len;
}
