#ifndef UART_H
#define UART_H

#include "board_status.h"
#include <stdint.h>
#include <stddef.h>

#define USART1_STATUS_REG         (*(volatile uint32_t*) 0x40013800)
#define USART1_DATA_REG           (*(volatile uint32_t*) 0x40013804)
#define USART1_BAUD_RATE_REG      (*(volatile uint32_t*) 0x40013808)
#define USART1_CR1_REG		  (*(volatile uint32_t*) 0x4001380c)

#define DEFAULT_BAUD_RATE	(9600)

#define USART_TX_TIMEOUT_TICKS	(3)
#define USART_TC_TIMEOUT_TICKS  (3)


typedef struct {
	uint32_t tick;
	uint8_t level;
	uint8_t id;
	int32_t value;
} log_record_t;


void usart1_init();

result_t usart1_write(const char* buf, const size_t len);

#endif /* UART_H */
