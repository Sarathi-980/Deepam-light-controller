#ifndef LOGGER_H
#define LOGGER_H

#include "board_status.h"
#include <stdint.h>


#define LOGGER_QUEUE_LENGTH             (10)                                                                   
#define LOGGER_QUEUE_ITEM_SIZE          (sizeof(log_record_t))

result_t logger_init();
result_t log_send(uint8_t msg_id, int32_t value);

#endif
