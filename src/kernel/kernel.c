#include <stddef.h>
#include <stdint.h>

#include "drivers/tty/tty.h"

#include "libs/kernel_log/kernel_log.h"
#include "libs/stdout/stdout.h"

#include "protected_mode/protected_mode.h"

#include "idt/interrupt_handlers.h"

#include "pic/pic.h"
#include "idt/idt.h"

/* MOVE THIS CODE LATER

const size_t CODES_PRESSED_SIZE = 59;
const char CODES_PRESSED[59] = {
	0,	 27,  '1',	'2',  '3',	'4', '5', '6',	'7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q',	'w', 'e', 'r',	't', 'y', 'u', 'i',
	'o', 'p', '[',	']',  '\n', 0,	 'a', 's',	'd', 'f', 'g', 'h',
	'j', 'k', 'l',	';',  '\'', '`', 0,	  '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm',	',',  '.',	'/', 0,	  0,	0,	 ' ', 0};

size_t HISTORY[VGA_HEIGHT];
*/

// system initialization function
void kernel_main(void)
{
	tty_initialize();

	protected_mode_enter();

	kernel_log(1, "couldn't start protected mode");
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
	pic_enable_all_irqs();
	__asm__ volatile("sti");
	kernel_log(0, "enabled interrupts");
}
