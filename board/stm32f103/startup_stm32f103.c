/********************************************************************************************
 * Startup code for STM32F103.
 * Defines the vector table, Reset Handler (copies .data section data from flash
 * to RAM, zeros the .bss section data and calls main) and default handler (Exception
 * functions are weak aliased to this function, can be overridden by defining a function with
 * same name elsewhere in code.
 ********************************************************************************************/

#include <stdint.h>

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

void Reset_Handler(void);
extern int main(void);

extern uint32_t _eram;

void Default_Handler(void);

void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

__attribute__((section(".isr_vector"), used))
uint32_t const vector_table[] = {
	(uint32_t) &_eram,		 // Main stack pointer. It is the first word fetched after reset
	(uint32_t) Reset_Handler,	 // Reset interrupt handler
	(uint32_t) NMI_Handler,		 // NMI interrupt handler (useful for clock security (HSE failure) and other important failures)
	(uint32_t) HardFault_Handler, 	 // Hard fault interrupt handler (Any system exceptions not handled (if not enabled) will be handled here)
	(uint32_t) MemManage_Handler,    // Memory Manage interrupt handler (memory violations like execute peripheral memory)
	(uint32_t) BusFault_Handler,	 // Bus fault interrupt handler
	(uint32_t) UsageFault_Handler,   // Usage fault interrupt handler (invalid use cases like ARM instructions use when only thumb supported)
	0,
	0,
	0,
	0,				 // 7 - 10 interrupts reserved
	(uint32_t) SVC_Handler,		 // Supervisor call exception
	(uint32_t) DebugMon_Handler,     // Debug monitor exception
	0,
	(uint32_t) PendSV_Handler,	 // Pendable service call
	(uint32_t) SysTick_Handler,	 // system tick timer interrupt handler
};

void Reset_Handler(void) {
	// Here &_sidata is address of flash memory where initialized data section starts, so we copy that data from flash to RAM 
	uint32_t *src = &_sidata;
	uint32_t *dest = &_sdata;
	uint32_t *end = &_edata;

	while (dest < end) {
		*dest++ = *src++;
	}

	dest = &_sbss;
	end = &_ebss;
	// Zeroing the .bss section. globals that are not initialized or initialized with 0 will be set to 0.
	while (dest < end) {
		*dest++ = 0;
	}

	// calling main function
	main();

	while(1);
}

// Unexpected interrupt. debugger will show it stopped here 
void Default_Handler(void) {
	while (1);   
}
