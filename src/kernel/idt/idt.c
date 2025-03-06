#include <stdint.h>

#include "idt.h"

#include "libs/kernel_log/kernel_log.h"

#include "idt/interrupt_handlers.h"

struct idt_entry idt_entries[IDT_INTERRUPT_LIMIT];
struct idt_pointer idt_pointer;

void idt_set_entry(int num, uint32_t base, uint16_t selector, uint8_t flags)
{
	// stop code if the number is incorrect
	if (num < 0 || num >= IDT_INTERRUPT_LIMIT)
	{
		kernel_log(1, "couldn't add IDT interrupt - incorrect table size");
		return;
	}

	struct idt_entry *idt_entry_target = &idt_entries[num];
	idt_entry_target->base_low = base & 0xFFFF;
	idt_entry_target->base_high = (base >> 16) & 0xFFFF;
	idt_entry_target->selector = selector;
	idt_entry_target->always_zero = 0;
	idt_entry_target->flags = flags;
}

void idt_load(void)
{
	kernel_log(3, "attempting to load the IDT");
	idt_pointer.limit = sizeof(idt_entries) - 1;
	idt_pointer.base = (uint32_t)(uintptr_t)&idt_entries;

	__asm__ volatile("lidt %0" : : "m"(idt_pointer));

	__asm__ volatile("sti");

	kernel_log(0, "loaded the IDT and enabled interrupts");
}

void idt_setup(void)
{
	kernel_log(3, "setting up the IDT");

	isr_handler_t *handlers = get_isr_handlers();
	for (int i = 0; i < IDT_INTERRUPT_LIMIT; i++)
		idt_set_entry(i, (uintptr_t)handlers[i], 0x08, 0x8E);

	kernel_log(0, "set up IDT interrupts");

	idt_load();
}
