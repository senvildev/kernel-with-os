#include <stdint.h>

#ifndef IDT_H
#define IDT_H

#define IDT_INTERRUPT_LIMIT 32

// structure used to create and
// define an interrupt in the IDT
struct idt_entry
{
	uint16_t base_low;	 // lower 16 bits of the address
	uint16_t selector;	 // which code segment to use when interrupting
	uint8_t always_zero; // always set to 0
	uint8_t flags;		 // how the interrupt has to behave
	uint16_t base_high;	 // upper 4 bits of the address
} __attribute__((packed));

// structure used to create a
// pointer to load the IDT
//	  - limit - size of the GDT
//	  - base  - where the address starts
struct idt_pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

// required variables
// stores the interrupts
extern struct idt_entry idt_entries[IDT_INTERRUPT_LIMIT];
// points to the IDT
extern struct idt_pointer idt_pointer;

#endif

// function that sets an interrupt in the IDT
// arguments:
//	  - num		  - which interrupt it is in the code
//
//	  - base	  - starting address of the IDT
//				  - in this case this is a pointer to
//				  - a function containing the ISR handler
//
//	  - selector  - specifies which code segment should
//				  - be used to execute the handler
//
//	  - flags	  - settings that control the behavior
//				  - of the interrupt
void idt_set_entry(int num, uint32_t base, uint16_t selector, uint8_t flags);

// function that loads the IDT, pretty straightforward
void idt_load(void);

// function that sets up all interrupts in the IDT
// and loads it in the end
void idt_setup(void);
