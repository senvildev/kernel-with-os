#include <stddef.h>
#include <stdint.h>

#include "drivers/bios_vga/bios_vga.h"

#include "libs/kernel_log/kernel_log.h"
#include "libs/stdout/stdout.h"

#include "protected_mode/protected_mode.h"

#include "idt/interrupt_handlers.h"

#include "pic/pic.h"
#include "idt/idt.h"

#include "drivers/input/keyboard/keyboard.h"
#include "os/os.h"

#include "global/defines.h"

// main kernel initialization function
void kernel_main(void)
{
	// initializes the BIOS VGA
	bios_vga_initialize();
	// enters protected mode
	protected_mode_enter();

	// halt the system in case it failed to
	// enter protected mode
	bios_vga_write_string("error: couldn't start protected mode");
	bios_vga_write_string("halting system.");
	for (;;)
		asm("hlt");
}

// kernel working under protected mode
void protected_kernel_main(void)
{
	bios_vga_clear();
	kernel_log(SUCCESS, "enabled and entered protected mode\n");
	// sets up the IDT
	idt_setup();
	print("\n");
	// sets up the PIC
	pic_setup();
	print("\n");

	kernel_log(INFO, "enabling interrupts");
	// enables interrupts using the sti opcode
	// in assembly
	__asm__ volatile("sti");
	kernel_log(SUCCESS, "enabled interrupts");

	// disables all IRQ's in the PIC
	pic_disable_all_irqs();

	// code to disable the cursor
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);

	// initializes the user level
	// commented out due to debug purposes
	// kernel_log(INFO, "initializing operating system");
	// initialize_system();

	// halt the system in case it reaches
	// this part
	for (;;)
		asm("hlt");
}
