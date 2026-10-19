#ifndef CLOCK_H
#define CLOCK_H

#include "board.h"

#define RCC_CR_REG      (*(volatile uint32_t*) 0x40021000)
#define RCC_CFG_REG     (*(volatile uint32_t*) 0x40021004)
#define RCC_APB2_EN_REG (*(volatile uint32_t*) 0x40021018)

#define FLASH_ACR_REG   (*(volatile uint32_t*) 0x40022000)


result_t clock_init();
#endif
