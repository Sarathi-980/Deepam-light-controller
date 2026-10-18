# ---------------------Deepam project make file------------------------------------

TARGET := deepam
BUILD := build

# -------------DIR PATH---------------------------

FREERTOS := third_party/FreeRTOS-Kernel
PORT := $(FREERTOS)/portable/GCC/ARM_CM3
LINKERSCRIPT := board/stm32f103/stm32f103x8.ld
			
	
C_FILES   := 	$(wildcard app/*.c) \
		$(wildcard app/src/*.c) \
	   	$(wildcard board/stm32f103/*.c) \
		$(wildcard board/*.c) \
		$(FREERTOS)/tasks.c \
		$(FREERTOS)/queue.c \
		$(FREERTOS)/list.c \
		$(FREERTOS)/timers.c \
		$(FREERTOS)/event_groups.c \
		$(PORT)/port.c

INCLUDES := -Iconfig -Iapp -Iapp/src -Iboard/stm32f103 -Iboard -I$(FREERTOS)/include -I$(PORT)

OBJS := $(addprefix $(BUILD)/, $(C_FILES:.c=.o))

DEPS := $(OBJS:.o:.d)


#----Tool chain----------

CROSS := arm-none-eabi-
CC := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy
SIZE := $(CROSS)size

#------FLAGS-------

CPU := -mcpu=cortex-m3 -mthumb
CFLAGS := $(CPU) $(INCLUDES) -std=c11 -Os -g3 -Wall -Wextra -Wshadow -MMD -MP
LFLAGS := $(CPU) -T$(LINKERSCRIPT) -nostartfiles --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map

#----targets------

.PHONY: all size flash clean


all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin size

$(BUILD)/$(TARGET).elf : $(OBJS) $(LINKERSCRIPT)
	$(CC) $(OBJS) $(LFLAGS) -o $@

$(BUILD)/$(TARGET).bin : $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

flash: $(BUILD)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $< verify reset exit"

clean:
	rm -rf $(BUILD)

-include $(DEPS)
