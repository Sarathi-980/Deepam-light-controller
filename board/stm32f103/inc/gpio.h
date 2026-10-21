/* Each general purpose I/O ports has two 32 bit configuration registers, two 32 bit data registers, a bit 32 bit set/reset register, a 16 bit reset         * register and a 32 bit locking register. 
 * To use external interrupt lines, we must configure in input mode.
 * The locking mechanism allows the IO configuration to be frozen, then it is no longer possible to modify the value of the port bit until reset.
 *
 */

#include <stdint.h>
#include "clock.h"
#include "board_status.h"
#include "board_config.h"

/* APB2 peripheral clock enables, I/O ports A to E, AFIO, ADC1, ADC2, SPI1, TIM1, USART1 */
#define GPIO_APB2_ENABLE_REG	(*(volatile uint32_t*) 0x40021018)


#define PORT_A_CFGL_REG		(*(volatile uint32_t*) 0x40010800)
#define PORT_A_CFGH_REG		(*(volatile uint32_t*) 0x40010804)
#define PORT_A_BSRR_REG		(*(volatile uint32_t*) 0x40010810)
#define PORT_C_CFGL_REG         (*(volatile uint32_t*) 0x40011000)
#define PORT_C_CFGH_REG         (*(volatile uint32_t*) 0x40011004)
#define PORT_C_BSRR_REG         (*(volatile uint32_t*) 0x40011010)


static inline void gpio_led_on() {
        PORT_C_BSRR_REG = (1U << (LED_PORTC_IO_PIN + 16U));
}

static inline void gpio_led_off() {
        PORT_C_BSRR_REG = (1U << LED_PORTC_IO_PIN);
}

typedef enum {
	GPIO_PUSH_PULL_MODE,
	GPIO_OPEN_DRAIN_MODE,
	AFIO_PUSH_PULL_MODE,
	AFIO_OPEN_DRAIN_MODE
} io_cfg_t;

typedef enum {
	OUTPUT_MODE_SPEED_10MHZ = 1U,
	OUTPUT_MODE_SPEED_2MHZ,
	OUTPUT_MODE_SPEED_50MHZ
} gpio_output_mode_t;

void gpio_init();
result_t gpio_led_init();
