#include "uart.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

extern uint32_t g_system_clock_freq;

/* We will use 8N1 USART1 communication, by default the control registers has this configuration */
void usart1_init() {
	USART1_BAUD_RATE_REG = (g_system_clock_freq + (DEFAULT_BAUD_RATE / 2)) / DEFAULT_BAUD_RATE;
	USART1_CR1_REG |= (1U << 13U) | (1U << 3U);
}

result_t usart1_put_char(char ch) {
	TickType_t start = xTaskGetTickCount();

	/* Waiting for TXE (Transmit data register) bit is set */
	while (!(USART1_STATUS_REG & (1U << 7U))) {
		if ((xTaskGetTickCount() - start) >= USART_TX_TIMEOUT_TICKS) {
			return RESULT_FAIL;
		}
	}

	USART1_DATA_REG = (uint32_t)ch;
	return RESULT_OK;
}

result_t usart1_write(const char* buf, const size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (usart1_put_char(buf[i]) != RESULT_OK) {
			return RESULT_FAIL;
		}
	}

	TickType_t start = xTaskGetTickCount();
	while (!(USART1_STATUS_REG & (1U << 6U))) {
		if ((xTaskGetTickCount() - start) >= USART_TC_TIMEOUT_TICKS) {
			return RESULT_FAIL;
		}
	}

	return RESULT_OK;
}
