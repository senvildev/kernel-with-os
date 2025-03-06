#include <stdint.h>

#ifndef IDT_H
#define IDT_H

#define IDT_INTERRUPT_LIMIT 32

struct idt_entry
{
	uint16_t base_low;
	uint16_t selector;
	uint8_t always_zero;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed));

struct idt_pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt_entries[IDT_INTERRUPT_LIMIT];
extern struct idt_pointer idt_pointer;

#endif

void idt_set_entry(int num, uint32_t base, uint16_t selector, uint8_t flags);

void idt_load(void);

void idt_setup(void);
