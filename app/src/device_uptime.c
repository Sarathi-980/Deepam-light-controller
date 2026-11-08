#include "device_uptime.h"
#include "board_status.h"
#include "FreeRTOS.h"
#include "timers.h"
#include <stdint.h>

static TimerHandle_t deviceUpTimerHandler = NULL;
static  StaticTimer_t deviceUpTimerStack;

static volatile uint32_t device_up_time_sec = 0;

void deviceUpTimerCounter(TimerHandle_t xTimer) {
        device_up_time_sec++;
}

uint32_t get_uptime_seconds(void) {
        return device_up_time_sec;
}

result_t device_uptime_init() {
        deviceUpTimerHandler = xTimerCreateStatic("UpCounter", pdMS_TO_TICKS(1000),
	        pdTRUE, NULL, deviceUpTimerCounter, &deviceUpTimerStack);
        if (deviceUpTimerHandler == NULL) {
               return RESULT_FAIL;
        }
        xTimerStart(deviceUpTimerHandler, 0);
	return RESULT_OK;
}


