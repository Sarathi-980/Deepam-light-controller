/*
 * FreeRTOS application hook for Deepam project
 *
 * These functions are required by settings in FreeRTOSConfig.h
 *
 *   - configSUPPORT_STATIC_ALLOCATION = 1 -> idle and timer task memory callbacks
 *   - configCHECK_FOR_STACK_OVERFLOW = 2 -> stack overflow hook (method 2)
 *
 *   The kernel call this functions; application doesn't
 */

#include "FreeRTOS.h"
#include "task.h"

/* -------------------------------------------------------------------------------------
 * Idle task memory
 *
 * With static allocation, the kernel cannot allocate the idle task's stack and control
 * block itself, so we provide them here. They are static and they exist for the 
 * whole lifetime.
 * -------------------------------------------------------------------------------------
 */

static StaticTask_t idle_task_tcb;
static StackType_t idle_task_stack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, 
		StackType_t **ppxIdleTaskStackBuffer, configSTACK_DEPTH_TYPE *puxIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer   = &idle_task_tcb;
	*ppxIdleTaskStackBuffer = idle_task_stack;
	*puxIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}

static StaticTask_t timer_task_tcb;
static StackType_t  timer_task_stack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    configSTACK_DEPTH_TYPE *puxTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer   = &timer_task_tcb;
    *ppxTimerTaskStackBuffer = timer_task_stack;
    *puxTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}


void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;        
    (void)pcTaskName;   /* Shows which task is overflowed */

    taskDISABLE_INTERRUPTS();
    for (;;) {
    }
}

