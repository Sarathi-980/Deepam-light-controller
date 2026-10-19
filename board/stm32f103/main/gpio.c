#include "gpio.h"

/*
 * the gpio_init function for initializing common requirements for GPIO
 *
 */
result_t gpio_init(void) {
	RCC_APB2_EN_REG |= (1U << 4U);
	return RESULT_OK;	
}

result_t gpio_led_init(void) {
	/* each port has 4 bits, first two for I/O mode with speed and next two I/O mode configuration
	 * here I wrote OUTPUT_2MHZ_SPEED for mode setting and PUSH_PULL (0) for port configuration for port 13
	 */
	PORT_C_CFGH_REG	|= (PORT_C_CFGH_REG & ~(0xFU << 20U)) | (OUTPUT_MODE_SPEED_2MHZ << 20U);
	return RESULT_OK;
}

