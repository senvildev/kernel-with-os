#include <stddef.h>
#include <stdint.h>

#include "tty/tty.h"
#include "gdt/gdt.h"

#include "libs/kernel_log/kernel_log.h"
#include "libs/stdout/stdout.h"

// #include "input/keyboard/keyboard.h"

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

	kernel_log(3, "setting up global descriptor table");
	gdt_setup();
	kernel_log(0, "set up global descriptor table");

	print("\nslava kokaini");
}
