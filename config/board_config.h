#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>
#include "clock.h"

extern uint32_t g_system_clock_freq;

#define LED_PORTC_IO_PIN	(13U)

#define BOARD_SYSCLK_HZ         (g_system_clock_freq)

#define LOGGER_TASK_PRIORITY	(4U)

#endif /* board_config_h */
