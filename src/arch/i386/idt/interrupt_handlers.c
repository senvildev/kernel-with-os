#include "libs/kernel_log/kernel_log.h"

#include <stdint.h>

#include "global/defines.h"

// code to run after each interrupt
void after_handle(void)
{
	__asm__ volatile("cli");

	while (1)
		__asm__ volatile("hlt");
}

// default handle for (potentially unknown)
// ISR's.
void handle_isr_default(void)
{
	kernel_log(ERROR, "unknown error lol cry abt it");
	after_handle();
}

// handle for division by zero
void handle_isr0(void)
{
	kernel_log(ERROR, "division by zero");

	after_handle();
}

// handle for a debug exception
void handle_isr1(void)
{
	kernel_log(ERROR, "debug exception");
	after_handle();
}

// handle for a non-maskable exception
void handle_isr2(void)
{
	kernel_log(ERROR, "non-maskable exception");
	after_handle();
}

// handle for a breakpoint exception
void handle_isr3(void)
{
	kernel_log(ERROR, "breakpoint exception");
	after_handle();
}

// handle for an overflow exception
void handle_isr4(void)
{
	kernel_log(ERROR, "overflow");
	after_handle();
}

// handle for a bounds check exception
void handle_isr5(void)
{
	kernel_log(ERROR, "bounds check exception");
	after_handle();
}

// handle for an invalid opcode
void handle_isr6(void)
{
	kernel_log(ERROR, "invalid opcode");
	after_handle();
}

// handle for an unavailable device
void handle_isr7(void)
{
	kernel_log(ERROR, "device not available");
	after_handle();
}

// handle for a double fault
void handle_isr8(void)
{
	kernel_log(ERROR, "double fault");
	after_handle();
}

// handle for a coprocessor argument overrun
void handle_isr9(void)
{
	kernel_log(ERROR, "coprocessor segment overrun");
	after_handle();
}

// handle for a bad TSS
void handle_isr10(void)
{
	kernel_log(ERROR, "bad TSS");
	after_handle();
}

// handle for a non-present segment
void handle_isr11(void)
{
	kernel_log(ERROR, "segment not present");
	after_handle();
}

// handle for a stack fault
void handle_isr12(void)
{
	kernel_log(ERROR, "stack fault");
	after_handle();
}

// handle for a general protection fault
void handle_isr13(void)
{
	kernel_log(ERROR, "general protection fault");
	after_handle();
}

// handle for a page fault
void handle_isr14(void)
{
	kernel_log(ERROR, "page fault");
	after_handle();
}

// handle for a reserved exception
void handle_isr15(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a x87 floating point error
void handle_isr16(void)
{
	kernel_log(ERROR, "x87 floating-point exception");
	after_handle();
}

// handle for an alignment check exception
void handle_isr17(void)
{
	kernel_log(ERROR, "alignment check exception");
	after_handle();
}

// handle for a machine check exception
void handle_isr18(void)
{
	kernel_log(ERROR, "machine check exception");
	after_handle();
}

// handle for a SIMD floating-point exception
void handle_isr19(void)
{
	kernel_log(ERROR, "SIMD floating-point exception");
	after_handle();
}

// handle for a virtualization exception
void handle_isr20(void)
{
	kernel_log(ERROR, "virtualization exception");
	after_handle();
}

// handle for a control protection exception
void handle_isr21(void)
{
	kernel_log(ERROR, "control protection exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr22(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr23(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr24(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr25(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr26(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr27(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr28(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr29(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}

// handle for a security exception
void handle_isr30(void)
{
	kernel_log(ERROR, "security exception");
	after_handle();
}

// handle for a reserved exception
void handle_isr31(void)
{
	kernel_log(ERROR, "reserved exception");
	after_handle();
}
