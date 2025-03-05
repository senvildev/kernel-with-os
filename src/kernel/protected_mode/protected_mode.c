#include "protected_mode.h"
#include "gdt/gdt.h"

#include "kernel.h"

#include "libs/kernel_log/kernel_log.h"

// main function to enter protected mode
void protected_mode_enter(void)
{
	kernel_log(3, "attempting to enter protected mode");
	__asm__ volatile("cli"); // disable interrupts
	kernel_log(3, "setting up GDT segments");
	// set up kernel segments
	gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF); // 1MB kernel code segment
	gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF); // 1MB kernel data segment
	// set up userspace segments
	gdt_set_entry(3, 0, 0xFFFFF, 0xFA, 0xCF); // 1MB userspace code segment
	gdt_set_entry(4, 0, 0xFFFFF, 0xF2, 0xCF); // 1MB userspace data segment
	kernel_log(0, "set up the GDT segments");
	gdt_load();

	kernel_log(3, "enabling protected mode");
	unsigned long cr0;
	// get the value of the cr0 register
	__asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
	cr0 |= 0x1; // change the PM bit to 1
	// move the enabled PM bit to the cr0 register
	__asm__ volatile("mov %0, %%cr0" : : "r"(cr0));

	__asm__ volatile("mov $0x10, %%ax;" // move gdt data segment into ax
					 "mov %%ax, %%ds;"	// move ax into data segment
					 "mov %%ax, %%es;"	// move ax into extra segment
					 "mov %%ax, %%ss;"	// move ax into stack segment
					 "call *%0;"		// call the main PM kernel function
					 "hlt;"
					 :
					 : "r"(protected_kernel_main) // store the function to work
												  // in during protected mode in
												  // a general purpose register
					 : "ax"); // tells the compiler that %ax will be modified
}
