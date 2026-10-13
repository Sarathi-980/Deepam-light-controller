/**************************************************************************************************
 *
 * FreeRTOSConfig.h - FreeRTOS is customized using this header file configuration. 
 * FreeRTOS designed in a way, it will run from 8-bit chips to large processors, so kernel
 * doesn't hardcode about system. 
 * The FreeRTOS reads this file at compile time, this file describes the hardware, what features
 * to include and configuration sizes and limits. 
 * ***********************************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "board_config.h"

#define configUSE_PREEMPTION				(1)	// High priority ready task runs immediately.
#define configUSE_TICKLESS_IDLE				(1)	// Sleep through idle period to save power
#define configUSE_IDLE_HOOK				(0)	// Not used
#define configUSE_TICK_HOOK				(0)	// Not used

#define configTICK_RATE_HZ				(100)	// 10 ms tick
#define configMAX_PRIORITIES				(5)	// 0 to 4 priorities
#define configMINIMAL_STACK_SIZE			(128) 	// stack size minimum in words
#define configTICK_TYPE_WIDTH_IN_BITS(0)	// 32 bit tick count
#define configIDLE_SHOULD_YIELD				(1) 	// No application uses priority 0, so default config

#define configCPU_CLOCK_HZ   				BOARD_SYSCLK_HZ	  

#define configSUPPORT_STATIC_ALLOCATION			(1)	// All tasks and queues is provided by the application at compile time so no heap fragmentation
#define configSUPPORT_DYNAMIC_ALLOCATION		(0)	// No heap used for application

/* The RTOS kernel check the stack pointer and the last 16 bytes 
 * within valid stack range to ensure that these known values have not been overwritten 
 */
#define configCHECK_FOR_STACK_OVERFLOW			(2)	// the stack overflow method 2 catches more cases than method 1
#define configUSE_MALLOC_FAILED_HOOK			(0) 	// No dynamic allocation, so it will never fail
#define configQUEUE_REGISTRY_SIZE			(8)	// maximum number of queues and semaphores can be registered. useful for debugging.
#define configMAX_TASK_NAME_LEN				(12)	// maximum task name length

// Task communication
#define configUSE_TASK_NOTIFICATIONS			(1)
#define configUSE_EVENT_GROUPS				(1)
#define	configUSE_MUTEXES				(1)
#define configUSE_RECURSIVE_MUTEXES			(0)
#define configUSE_COUNTING_SEMAPHORES			(0)
#define configUSE_QUEUE_SETS				(0)

#define configUSE_TIMERS				(1) 	// enables software timers
#define configTIMER_TASK_PRIORITY      			(3) 
#define configTIMER_QUEUE_LENGTH       			(5) 
#define configTIMER_TASK_STACK_DEPTH   			(configMINIMAL_STACK_SIZE * 2) 

#define INCLUDE_vTaskDelay				(1) 	// simple delay
#define INCLUDE_xTaskDelayUntil				(1)	// exact time interval delay
#define INCLUDE_vTaskSuspend				(1) 	// Required for portMAX_DELAY

#define configPRIO_BITS                         	(4) 	// STM32F103 implements 4 priority bits
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 	(15)
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    (5)

#define configKERNEL_INTERRUPT_PRIORITY \
        (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
        (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

#define vPortSVCHandler      				SVC_Handler
#define xPortPendSVHandler   				PendSV_Handler
#define xPortSysTickHandler  				SysTick_Handler

#define configASSERT(x)					do { if((x) == 0) { taskDISABLE_INTERRUPTS(); for (;;); } } while (0)

#endif
