#include "board.h"

static uint32_t board_state = 0;

result_t board_init(void) {
	result_t res = clock_init();
	if (res != RESULT_OK) {
		board_state |= BOARD_CLOCK_INIT_FAIL;
	}

	gpio_init();

	return RESULT_OK;
}
