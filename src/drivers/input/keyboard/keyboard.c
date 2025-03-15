#include <stdint.h>
#include <stddef.h>

#include "keyboard.h"

#include "pic/pic.h"
#include "idt/idt.h"

#include "drivers/tty/tty.h"

#include "libs/stdout/stdout.h"

const size_t CODES_PRESSED_SIZE = 59;
const char CODES_PRESSED[59] = {
	0,	 27,  '1',	'2',  '3',	'4', '5', '6',	'7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q',	'w', 'e', 'r',	't', 'y', 'u', 'i',
	'o', 'p', '[',	']',  '\n', 0,	 'a', 's',	'd', 'f', 'g', 'h',
	'j', 'k', 'l',	';',  '\'', '`', 0,	  '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm',	',',  '.',	'/', 0,	  0,	0,	 ' ', 0};

extern void keyboard_handler_asm(void);

void keyboard_handler(void)
{
	int scan_code = inb(0x64);
	pic_send_eoi(1);
	print("\ndone");
}

void initialize_keyboard(void)
{
	tty_clear();
	print("\ninitializing keyboard");
	idt_set_entry(0x21, (uint32_t)(uintptr_t)keyboard_handler_asm, 0x08, 0x8E);

	pic_enable_irq(1);

	print(" - initialized\n");
}
