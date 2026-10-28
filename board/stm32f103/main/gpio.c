#include "gpio.h"

/* gpio init function to initialize */
void gpio_init(void) {
	/* Enabling I/O port A and port C */
	RCC_APB2_EN_REG = (1U << 4U) | (1U << 2U);
}

result_t gpio_led_init(void) {

	/* each port has 4 bits, first two for I/O mode with speed and next two I/O mode configuration
	 * here I wrote OUTPUT_2MHZ_SPEED for mode setting and PUSH_PULL (0) for port configuration for port 13
	 */
	PORT_C_CFGH_REG	= (PORT_C_CFGH_REG & ~(0xFU << 20U)) | (OUTPUT_MODE_SPEED_2MHZ << 20U);
	return RESULT_OK;
}

result_t gpio_usart1_tx_init(void) {
	/* To use USART1 we first make it alternate function input output (AFIO) and then the USART peripheral 
	 * will be connected to the pins based on remapping bits in AFIO_MAPR register. 
	 * by default the USART1 TX and RX functions will be connected to PA9 and PA10.
	 *
	/* Setting port A output 2 MHz mode and AFIO push pull */
	PORT_A_CFGH_REG = (PORT_A_CFGH_REG & ~(0xFU << 4U)) | (2U << 6U) | (OUTPUT_MODE_SPEED_2MHZ << 4U);
	return RESULT_OK;
}


