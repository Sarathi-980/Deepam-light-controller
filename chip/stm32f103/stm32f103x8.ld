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

ENTRY(Reset_Handler) 	// Entry point of an application, so it is the first executable instruction in the output file (first byte of .elf or executable file)

// Memory declares memory regions with attributes specifying whether the region can be read from, written to or executable. 
MEMORY {
	FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 64k   // Flash memory size is 64 KB
	RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 20k    // RAM memory size is 20 KB
}

SECTIONS {
	.text :
	{
		KEEP(*(.isr_vector))		// Keep statement tells the linker, keep the section even if no symbols inside are referenced.
		*(.startup*)			
		*(.text*)
		*(.rodata*)
	} > FLASH

	.ARM.exidx :             // ARM index table, used for stack unwinding (walking back up the chain of function calls)
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

	_sidata = LOADADDR(.data);	// address of data section in flash memory

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

     // Checking minimum 1 kb of stack is available to continue, if not linker will throw error
      ._stack_check {
	     . = ALIGN(8);	// Stack pointer should be aligned to 8 byte according to ARM calling standard
	     . = . + 0x400;     /* minimum 1 kb for the main stack */
	     . = ALIGN(8);
	} > RAM

     }

    _eram = ORIGIN(RAM) + LENGTH(RAM);	// end of RAM address, since RAM grows downward (pushing a value will decrease the stack pointer by 4)
