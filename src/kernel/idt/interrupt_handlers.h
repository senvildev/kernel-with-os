#include <stdint.h>

#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

typedef void (*isr_handler_t)(void);

// assembly interrupt handlers
extern void isr_default(void);
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

static inline isr_handler_t *get_isr_handlers(void)
{
	static isr_handler_t handlers[] = {
		isr0,  isr1,  isr2,	 isr3,	isr4,  isr5,  isr6,	 isr7,
		isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15,
		isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
		isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31};
	return handlers;
}

// C code handlers are inside the respective C file

#endif
