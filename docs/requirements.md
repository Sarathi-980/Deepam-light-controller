# Requirements 

Lists functional and non-functional requirements the project.

## Functional Requirements

- **FR-01:** The device shall switch the lamp on when the day/light state machine confirms dusk.
- **FR-02:** The device shall switch the lamp off when the day/light state machine confirms dawn.
- **FR-03:** The device shall dim the lamp in stages through the night using a dusk-relative schedule.
- **FR-04:** The device shall learn the length of each night, estimate midnight from it, and store the learned value in flash so it survives a power loss.
- **FR-05:** The device shall measure battery voltage, battery current, and the energy harvested during the day using an INA226 on the battery line.
- **FR-06:** When the day/night state machine confirms dusk, and before the lamp is switched on, the device shall calculate a night-time power budget from the battery's state of charge, a reserve for cloudy days, and the learned night length, and scale the dimming schedule to fit it.
- **FR-07:** During the night, the device shall adjust the brightness if actual consumption differs from the plan.
- **FR-08:** The device shall reduce lamp brightness when battery voltage falls below a low threshold, and switch the lamp off below a critical threshold.
- **FR-09:** The device shall switch the lamp off and report a fault if the lamp current exceeds the maximum defined in the lamp profile.
- **FR-10:** If the device starts at night without harvest data, it shall estimate state of charge from battery voltage and use a conservative default schedule until a full day-night cycle has been recorded.
- **FR-11:** If one light sensor fails, the device shall detect the failure and continue using the remaining sensor.
- **FR-12:** Lamp limits, thresholds, and the dimming schedule shall be selectable at compile time through lamp profiles.
- **FR-13:** The device shall log sensor readings and state changes over UART for tuning and debugging.


## Non Functional Requirements

- **NFR-01:** The device shall draw a average current below x mA during the day (later confirmed by meaurement).
- **NRF-02:** Commands received from a host shall be treated as requests.
- **NRF-03:** Each sensor shall provide a valid readings every N seconds (configurable). A sensor fails to do so shall be marked faulty.
- **NRF-04:** Adding a lamp profile shall require only a configuration file with no changes to application or driver code.
- **NRF-05:** The device shall recover from software hang using a watchdog, with 2 seconds.
- **NRF-06:** After power loss, the device must resume correct operation.
- **NRF-07:** Fault shall be reported in logs message or LED blinks.
- **NRF-08:** The device shall operate at least a year continuously (target).
- **NRF-09:** The device shall operate hard temperatures (target).


## Future Requirements

- **FR-F01:** The device shall provide an interface for a Linux host to read logs and status remotely, enabling remote monitoring (RMS) over the internet through the host.
- **FR-F02:** A Linux driver shall expose the device's sensors and lamp control to the host system.
- **FR-F03:** The device shall accept control commands (mode, brightness, thresholds) from a host over Modbus RTU on RS-485.
- **FR-F04:** In MANUAL mode, the device shall return to AUTO mode if no valid host message is received within a set timeout.
- **FR-F05:** Battery and lamp safety limits shall remain enforced in all modes, including MANUAL.

## Contraints

- **C-01:** STM32F103, register-level drivers, No HAL or CMSIS.
- **C-02:** FreeRTOS for scheduling.
- **C-03:** The device powered by battery.
- **C-04:** Battery charging and low-level disconnect are handled by solar charger controller to protect battery.
