# Project Architecture

Deepam controls a solar-powered LED lamp for the temple use, adjusting its brightness through the night based on the energy harvested during the day.
Many temples are run by small groups or families who bear the cost of overnight lighting; Deepam lets them keep the lamp lit using solar energy and provides efficient energy usage using autonomous lighting.

## Overview

The firmware written in C with register-level drivers (no HAL), the FreeRTOS for task scheduling, and pure C algorithms with no hardware access. So they can be tested on a PC. If one light sensor fails, the device continues in degraded mode using the remaining sensor.

## Inter-task Communication

- **Sensor -> Control:** a mailbox (queue length 1, written with xQueueOverwrite) control task gets the latest readings.
- **Health monitoring:** each task sets its bit in event group every cycle.
- **Any task -> log:** a queue of fixed size log records, log task formats and sends as a log over UART.

## Sensors

| Sensor | Role |
|---|---|
| LDR | outdoor light intensity detection |
| Solar panel voltage | day and night signal independent of battery state, and redundancy for LDR |
| INA226 | battery voltage, current and energy | 

## Tasks 

| Task | Responsibility | Priority |
|---|---|---|
| Monitor | Checks every task is alive, feeds the watchdog | 4 (High) |
| Control | State machine, schedule, energy budget, PWM, battery | 3 |
| Sensor | Reads ADC and INA226, filters, detect faults | 2 |
| log | Formats and sends logs message over UART | 1 (low) |

## Safety

- **Lamp over-current (FR-09):** the INA226 alert pin triggers a EXTI interrupt, then the ISR sets PWM duty to 0.
- **Low battery (FR-08):** the control task dims the lamp when below low threshold and switches off below a critical threshold.
- **Firmware hang:** the monitor task feeds the Independent watchdog (IWDG) only when every task has reported in. A stuck causes a reset.

## Reliability

Static allocation avoids heap fragmentation over months of unattended operation.
Stack overflow checking and configASSERT enabled during development.
The unit tests for the algorithms.

## Future

A communication task will be implemented with Modbus RTU over RS-485, allowing a Linux host to monitor or control the device.
Host commands are treated as requests. 
