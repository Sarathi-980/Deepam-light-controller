#include "logger.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include "board_config.h"

static StaticQueue_t sLogQueue;
static QueueHandle_t loggerQueue;

#define LOGGER_TASK_STACK_SIZE		(256U)

static TaskHandle_t loggerTaskHandle;
static StaticTask_t loggerTaskTCB;
static StackType_t loggerTaskStack[LOGGER_TASK_STACK_SIZE];

static uint8_t sLogQueueStorageArea[LOGGER_QUEUE_LENGTH * LOGGER_QUEUE_ITEM_SIZE];

static void logger_task(void* arg) 
{
	log_record_t current_log;
	char log_buf[64];

	while (1) {
		if (xQueueReceive(loggerQueue, &current_log, portMAX_DELAY) == pdPASS) {
			size_t len = snprintf(log_buf, sizeof(log_buf), "Msg ID: %u, value: %ld\r\n", current_log.id, current_log.value);
			usart1_write(log_buf, len);
		}
	}

}


result_t logger_init() {
	loggerQueue = xQueueCreateStatic(LOGGER_QUEUE_LENGTH, LOGGER_QUEUE_ITEM_SIZE, 
				sLogQueueStorageArea, &sLogQueue);
	if (loggerQueue == NULL) {
		return RESULT_FAIL;
	}

	loggerTaskHandle = xTaskCreateStatic(logger_task, "LOGGER",
		       		LOGGER_TASK_STACK_SIZE, NULL, LOGGER_TASK_PRIORITY,
				loggerTaskStack, &loggerTaskTCB);
	if(loggerTaskHandle == NULL) {
		return RESULT_FAIL;
	}
	return RESULT_OK;
}

result_t log_send(uint8_t msg_id, int32_t value) 
{
	log_record_t log = {
		.tick = xTaskGetTickCount(),
		.id = msg_id,
		.value = value,
	};

	if (loggerQueue) {
		if (xQueueSend(loggerQueue, (void*) &log, 0) == pdPASS) {
			return RESULT_OK;
		}
	}

	return RESULT_FAIL;
}
