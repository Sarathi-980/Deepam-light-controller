# ANALOG TO DIGITAL CONVERTER (ADC)

The ADC is stored as 12 bit data as approximation of analog-to-digital converter. The ADC peripheral task is collecting ADC data from the Solar panel, LDR sensor and etc, which is the inputs for the dusk based scheduling algorithm.

## ADC hardware

- The ADC has up to 18 multiplexed channels allowing measuring signals from 16 external channels and 2 interal channels. The result of ADC stored in a left aligned or right 16 bit data register aligned based on configuration. 
- The Analog Watchdog (AWD) hardware feature allows application to detect if the input voltage goes outside user-defined high or low thresolds. 
- The ADC clock must not exceed more than 14 MHz.

### Features

- 12 bit resolution
- Interrupt generation at End of Conversion, End of injected conversion and Analog watchdog event
- Single and continuous conversion mode.
- Scan mode for automatic conversion of channel 0 to channel n.
- Self-calibration
- External trigger option for both regular and injected conversions.
- ADC Conversion time (STM32F103x) 1 microsecond at 56 MHz
- ADC power supply must be 2.4 V to 3.6 V
- DMA request generation during regular channel conversion

### ADC 

- ADC clock provided by clock controller is synchronous with the PCLK2 (APB2 clock).
- ADC powered-on by ADON bit in the ADC_CR2 register. 
- REGULAR GROUP : The regular group composed of up to 16 conversions. The regular group channels and their order must be selected in the ADC_SQRx register. 
- INJECTED GROUP : It is composed of up to 4 conversions. The injected channels and their order must be selected in the ADC_JSQR register. 
- ADC scan mode: It can be selected by setting the SCAN bit, the ADC scans all the channels selected in the ADC_SQRx registers. The DMA must be enabled, which is used to transfer the sampled adc daa to the SRAM.
- Discontinous mode: The sequence of conversion in SQRx registers will be parted n conversions. 
- Injected mode: 
- ADC samples the input voltage based on number of clock cycles, it can configured using SMP registers and **each channel can be sampled different sampling time**. 
- Since converted values stored in unique data register, it is necessary to use DMA for more than one regular channel sampling. 

