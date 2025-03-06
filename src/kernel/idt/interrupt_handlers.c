#include "libs/kernel_log/kernel_log.h"
#include "libs/stdout/stdout.h"

void after_handle(void)
{
	while (1)
		asm volatile("hlt");
}

void handle_isr_default(void)
{
	kernel_log(1, "unknown error lol cry abt it");
	after_handle();
}

void handle_isr0(void)
{
	kernel_log(1, "division by zero");

	after_handle();
}

void handle_isr1(void)
{
	kernel_log(1, "debug exception");
	after_handle();
}

void handle_isr2(void)
{
	kernel_log(1, "non-maskable exception");
	after_handle();
}

void handle_isr3(void)
{
	kernel_log(1, "breakpoint exception");
	after_handle();
}

void handle_isr4(void)
{
	kernel_log(1, "overflow");
	after_handle();
}

void handle_isr5(void)
{
	kernel_log(1, "bounds check exception");
	after_handle();
}

void handle_isr6(void)
{
	kernel_log(1, "invalid opcode");
	after_handle();
}

void handle_isr7(void)
{
	kernel_log(1, "device not available");
	after_handle();
}

void handle_isr8(void)
{
	kernel_log(1, "double fault");
	after_handle();
}

void handle_isr9(void)
{
	kernel_log(1, "coprocessor segment overrun");
	after_handle();
}

void handle_isr10(void)
{
	kernel_log(1, "bad TSS");
	after_handle();
}

void handle_isr11(void)
{
	kernel_log(1, "segment not present");
	after_handle();
}

void handle_isr12(void)
{
	kernel_log(1, "stack fault");
	after_handle();
}

void handle_isr13(void)
{
	kernel_log(1, "general protection fault");
	after_handle();
}

void handle_isr14(void)
{
	kernel_log(1, "page fault");
	after_handle();
}

void handle_isr15(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr16(void)
{
	kernel_log(1, "floating-point error");
	after_handle();
}

void handle_isr17(void)
{
	kernel_log(1, "alignment check exception");
	after_handle();
}

void handle_isr18(void)
{
	kernel_log(1, "machine check exception");
	after_handle();
}

void handle_isr19(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr20(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr21(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr22(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr23(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr24(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr25(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr26(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr27(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr28(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr29(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr30(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}

void handle_isr31(void)
{
	kernel_log(1, "reserved exception");
	after_handle();
}
