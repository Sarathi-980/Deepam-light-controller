/**************************************************************************************************************************************************
 * This linker script is for STM32 blue pill (STM32F103C8T6).
 * Flash : 64 KB starting at 0x08000000
 * RAM : 20 KB starting at 0x20000000
 *
 * On Reset, the Cortex-M3 reads the vector table from address 0x00000000. On the STM32 with BOOT0 is low, flash aliased to address 0, so vector table must 
 * be placed at the starting of the flash address.
 *
 * Vector table at 0x00000000 has initial stack pointer, next word of vector table contains the address of the reset handler.
 * The hardware loads the stack pointer before executing any code, so the reset handler can be written in C and any early exception (NMI, hardfault) can 
 * be handled with valid stack.
 * *************************************************************************************************************************************************/

ENTRY(Reset_Handler)

MEMORY {
	FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 64k
	RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS {
	.text :
	{
		KEEP(*(.isr_vector))
		*(.startup*)
		*(.text*)
		*(.rodata*)
	} > FLASH

	.ARM.exidx :
	{
		*(.ARM.exidx*)
	} > FLASH

	.data :
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > RAM AT > FLASH

	_sidata = LOADADDR(.data);

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		_sbss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		_ebss = .;
	} > RAM

	end = .;
	__end = .;


     ._stack_check {
	     . = ALIGN(8);
	     . = . + 0x400;     /* minimum 1 kb for the main stack */
	     . = ALIGN(8);
	} > RAM

     }

    _eram = ORIGIN(RAM) + LENGTH(RAM);
