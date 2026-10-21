#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"

static StaticTask_t blink_tcb;
static StackType_t  blink_stack[128];

static void blink_task(void *arg)
{
    for (;;) {
        gpio_led_on();
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_led_off();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    result_t res = board_init();
    if (res != RESULT_OK) {
	    // setting the clock fail bit
    }

    gpio_led_init();

    xTaskCreateStatic(blink_task, "blink", 128, NULL, 1,
                      blink_stack, &blink_tcb);
    vTaskStartScheduler();
    for (;;) {}
}
