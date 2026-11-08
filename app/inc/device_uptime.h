#ifndef DEVICE_UP_TIME
#define DEVICE_UP_TIME

#include "board_status.h"
#include <stdint.h>

uint32_t get_uptime_seconds();

result_t device_uptime_init();

#endif
