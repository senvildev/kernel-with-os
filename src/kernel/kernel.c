#include <stddef.h>
#include <stdint.h>

#include "drivers/tty/tty.h"

#include "libs/kernel_log/kernel_log.h"
#include "libs/stdout/stdout.h"

#include "protected_mode/protected_mode.h"

#include "idt/interrupt_handlers.h"

#include "pic/pic.h"
#include "idt/idt.h"

#include "drivers/input/keyboard/keyboard.h"
#include "os/os.h"

// system initialization function
void kernel_main(void)
{
	tty_initialize();

	protected_mode_enter();

	kernel_log(1, "couldn't start protected mode");

	for (;;)
		asm("hlt");
}

// kernel working under protected mode
void protected_kernel_main(void)
{
	kernel_log(0, "enabled and entered protected mode\n");

	idt_setup();
	print("\n");

	pic_setup();
	print("\n");

	kernel_log(3, "enabling interrupts");
	__asm__ volatile("sti");
	kernel_log(0, "enabled interrupts");

	pic_disable_all_irqs();

	kernel_log(3, "initializing operating system");
	initialize_system();

	for (;;)
		asm("hlt");
}
