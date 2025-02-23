#include <stddef.h>
#include <stdint.h>

#include "tty/tty.h"

static inline uint8_t inb(uint16_t port)
{
	uint8_t result;
	__asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
	return result;
}

const size_t CODES_PRESSED_SIZE = 59;
const char CODES_PRESSED[59] = {
	0,	 27,  '1',	'2',  '3',	'4', '5', '6',	'7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q',	'w', 'e', 'r',	't', 'y', 'u', 'i',
	'o', 'p', '[',	']',  '\n', 0,	 'a', 's',	'd', 'f', 'g', 'h',
	'j', 'k', 'l',	';',  '\'', '`', 0,	  '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm',	',',  '.',	'/', 0,	  0,	0,	 ' ', 0};

size_t HISTORY[VGA_HEIGHT];

void kernel_main(void)
{
	tty_initialize();

	uint8_t last_scancode;

	while (1)
	{
		if (tty_row > VGA_HEIGHT - 1)
			tty_row = 0;

		uint8_t scancode = inb(0x60);

		if (!scancode)
			continue;

		if (last_scancode == scancode)
			continue;

		if (scancode & 0x80)
		{
			last_scancode = 0;
			continue;
		}

		if (scancode > CODES_PRESSED_SIZE - 1)
			continue;

		last_scancode = scancode;

		char key = CODES_PRESSED[scancode];

		if (key == '\b')
		{
			if (tty_column == 0)
			{
				if (tty_row == 0)
					continue;
				tty_row -= 1;
				tty_column = HISTORY[tty_row];
			}
			else
			{
				tty_column -= 1;
				tty_insert_entry(0);
				HISTORY[tty_row] -= 1;
				tty_column -= 1;
			}
		}
		else if (key == '\n')
		{
			tty_row += 1;
			tty_column = 0;
		}
		else if (key == 0)
		{
			continue;
		}
		else
		{
			HISTORY[tty_row] += 1;
			tty_insert_entry(key);
		}
	}
}
