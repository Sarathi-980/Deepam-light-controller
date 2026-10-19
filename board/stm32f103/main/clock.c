#include <stdint.h>
#include "clock.h"


// I use 0xFFFF timeout, we can increase timeout.
#define CLOCK_WAIT_STATE(condition)	({							\
							uint32_t cond_met = 0;			\
							uint32_t count = 0x0000FFFF;		\
							do { 					\
								if (condition) {		\
									cond_met = 1;		\
									break;			\
								}				\
								count--;			\
							} while (count > 0);			\
							cond_met;				\
						})


uint32_t  g_system_clock_freq= 8000000U;



/***********************************************************************************************
 * When system starts or resets, it will use HSI clock. To change to clock frequency to 72 MHz
 * we use HSE external clock, with PLL multiplication factor we can get 72 MHz clock signal.
 * The AHB and APB2 bus maximum frequency is 72 MHz and APB1 maximum frequency is 36 MHz.
 * We use prescalers to change the frequency according to our requirements.
 *
 * **Note**: I wrote this function, the registers having a reset value. If this function fails,
 * system doesn't need to stop execution, the system will run on HSI. Because 2 wait states
 * for flash access will costs performance, and other prescaler are okay. For systick timer
 * we configure the freeRTOS runtime with global variable for system clock. 
 */
result_t clock_init() {
	/* HSE clock enable */
	RCC_CR_REG |= (1U << 16U);
	/* Waiting for HSE to stable */
	if (CLOCK_WAIT_STATE(RCC_CR_REG & (1U << 17U)) == 0U) {
		       return RESULT_FAIL;
	}	       
	/* FLASH_ACR register used to enable/disable prefetch and half cycle access and to control flash memory access */
	/* Since reset value is 0x30, doing OR operation on 4th bit not a problem, and the last three bits indicates wait 
	 * states of sys clock to the flash access time. */
	RCC_CFG_REG |= (1U << 4U) | 2U; /* enable prefetch and setting two wait states */
	
	/* We use 72 MHz for AHB and APB2 and 36 MHz for APB1 */
	RCC_CFG_REG |= (4U << 8U); /* HCLK clock is divided by 2 for APB1*/
	
	/* Setting HSE as PLL clock source */
	RCC_CFG_REG |= (1U << 16U);

	/* Multiplying with PLL multiplication factor, with 8 MHz external clock we use 9 as multiplication factor */
	RCC_CFG_REG |= (7U << 18U);

	/* Setting PLL on */
	RCC_CR_REG |= (1U << 24U);
	/* Waiting for PLL to stable */
	if (CLOCK_WAIT_STATE(RCC_CR_REG & (1U << 25U)) == 0U) {
		return RESULT_FAIL;
	}
	
	/* Switching the system clock to PLL */
	RCC_CFG_REG |= 2U;

	/* Checking the switch status */
	if (CLOCK_WAIT_STATE(RCC_CFG_REG & (2U << 2U)) == 0U) {
		return RESULT_FAIL;
	}

	g_system_clock_freq = 72000000U;

	return RESULT_OK;
}
