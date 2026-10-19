#ifndef BOARD_H
#define BOARD_H

#include "board_config.h"

typedef enum {
        RESULT_OK,
        RESULT_FAIL,
} result_t;

typedef enum {
	BOARD_CLOCK_INIT_FAIL = (1 << 0),
} board_state_t;


#endif /* BOARD_H */
