#ifndef UART_H
#define UART_H

#include "board_status.h"

#define USART1_STATUS_REG         (*(volatile uint32_t*) 0x40013800)
#define USART1_DATA_REG           (*(volatile uint32_t*) 0x40013804)
#define USART1_BAUD_RATE_REG      (*(volatile uint32_t*) 0x40013808)
#define USART1_CR1_REG		  (*(volatile uint32_t*) 0x4001380c)

#define DEFAULT_BAUD_RATE	(9600)

#define USART_TX_TIMEOUT_TICKS	(3)
#define USART_TC_TIMEOUT_TICKS  (3)

void usart1_init();

result_t usart1_put_char(char ch);


#endif /* UART_H */
