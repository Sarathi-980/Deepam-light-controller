#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/* Register addresses (temporary: move to chip/stm32f103 later) */
#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)
#define GPIOC_BSRR  (*(volatile uint32_t *)0x40011010)

static StaticTask_t blink_tcb;
static StackType_t  blink_stack[128];

static void blink_task(void *arg)
{
    (void)arg;
    for (;;) {
        GPIOC_BSRR = (1u << (13 + 16));  /* PC13 low = LED on */
        vTaskDelay(pdMS_TO_TICKS(500));
        GPIOC_BSRR = (1u << 13);         /* PC13 high = LED off */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    RCC_APB2ENR |= (1u << 4);                       /* GPIOC clock */
    GPIOC_CRH = (GPIOC_CRH & ~(0xFu << 20)) | (0x2u << 20); /* PC13 out 2MHz push-pull */

    xTaskCreateStatic(blink_task, "blink", 128, NULL, 1,
                      blink_stack, &blink_tcb);
    vTaskStartScheduler();
    for (;;) {}
}
