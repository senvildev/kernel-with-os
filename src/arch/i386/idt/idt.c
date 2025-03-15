#include <stdint.h>

#include "idt.h"

#include "libs/kernel_log/kernel_log.h"

#include "interrupt_handlers.h"

// declare the IDT variable
struct idt_entry idt_entries[IDT_INTERRUPT_LIMIT];
// declare the IDT pointer
struct idt_pointer idt_pointer;

// function to set an entry in the IDT
void idt_set_entry(int num, uint32_t base, uint16_t selector, uint8_t flags)
{
	// stop code if the number is incorrect
	if (num < 0 || num >= IDT_INTERRUPT_LIMIT)
	{
		kernel_log(1, "couldn't add IDT interrupt - incorrect table size");
		return;
	}

	// create a pointer to an IDT entry
	struct idt_entry *idt_entry_target = &idt_entries[num];

	// store memory address of the interrupt
	// mask the lower 16 bits
	idt_entry_target->base_low = (uint16_t)(base & 0xFFFF);
	// mask the upper 16 bits
	idt_entry_target->base_high = (uint16_t)(base >> 16);

	// store which code segment to use
	// straightforward
	idt_entry_target->selector = (uint16_t)selector;

	// reserved, always zero, straightforward
	idt_entry_target->always_zero = 0;

	// store settings on how the interrupt has to behave
	// straightforward
	idt_entry_target->flags = (uint16_t)flags;
}

// function to load the IDT using assembly
void idt_load(void)
{
	kernel_log(3, "attempting to load the IDT");
	// set the limit of the IDT pointer
	idt_pointer.limit = sizeof(idt_entries) - 1;
	// set the starting address of the IDT pointer
	idt_pointer.base = (uint32_t)(uintptr_t)&idt_entries;
	// load the IDT using assembly
	__asm__ volatile("lidt (%0)" : : "r"(&idt_pointer));

	kernel_log(0, "loaded the IDT");
}

// function to set the IDT up
void idt_setup(void)
{
	kernel_log(3, "setting up the IDT");
	// get the list of assembly ISR's and the handlers
	isr_handler_t *handlers = get_isr_handlers();
	for (int i = 0; i < IDT_INTERRUPT_LIMIT; i++)
		// loop through each one and set them in the IDT
		idt_set_entry(i, (uintptr_t)handlers[i], 0x08, 0x8E);

	kernel_log(0, "set up IDT interrupts");
	// loads the IDT
	idt_load();
}
