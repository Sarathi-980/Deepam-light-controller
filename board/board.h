#ifndef BOARD_H
#define BOARD_H

#include "board_config.h"
#include "clock.h"
#include "gpio.h"

typedef enum {
	BOARD_CLOCK_INIT_FAIL = (1 << 0),
} board_state_t;


result_t board_init();
#endif /* BOARD_H */
