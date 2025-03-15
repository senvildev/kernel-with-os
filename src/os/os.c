#include "drivers/tty/tty.h"

#include "libs/stdout/stdout.h"

#include "drivers/input/keyboard/keyboard.h"

#include "pic/pic.h"

void initialize_system(void)
{
	tty_clear();
	print("Hello, OS!");
	initialize_keyboard();
}
