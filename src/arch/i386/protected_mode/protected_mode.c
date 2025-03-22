#include "protected_mode.h"
#include "../gdt/gdt.h"

#include "kernel/kernel.h"

#include "drivers/bios_vga/bios_vga.h"

#include "global/defines.h"

extern void protected_mode_switch(void);

// main function to enter protected mode
void protected_mode_enter(void)
{
	bios_vga_write_string("info: attempting to enter protected mode");
	__asm__ volatile("cli"); // disable interrupts
	bios_vga_write_string("setting up GDT segments");
	gdt_set_entry(0, 0, 0x00000, 0x00, 0x00);
	// set up kernel segments
	gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF); // 1MB kernel code segment
	gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF); // 1MB kernel data segment
	// set up userspace segments
	gdt_set_entry(3, 0, 0xFFFFF, 0xFA, 0xCF); // 1MB userspace code segment
	gdt_set_entry(4, 0, 0xFFFFF, 0xF2, 0xCF); // 1MB userspace data segment
	bios_vga_write_string("succes: set up the GDT segments");

	// load the GDT
	gdt_load();

	bios_vga_write_string("info: enabling protected mode");

	// switch to protected mode using an assembly function
	protected_mode_switch();
}
