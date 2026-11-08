#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"

int main(void)
{
    result_t res = board_init();
    if (res != RESULT_OK) {
	    // setting the clock fail bit
    }


    vTaskStartScheduler();
    for (;;) {}
}
