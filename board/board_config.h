#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H


typedef enum {
	RESULT_OK,
	RESULT_FAIL,
} result_t;

extern uint32_t g_system_clock_freq;
#define BOARD_SYSCLK_HZ		(g_system_clock_freq)


#endif /* board_config_h */
