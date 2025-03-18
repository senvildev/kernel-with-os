#include "drivers/tty/tty.h"

#include "libs/stdout/stdout.h"

#include "drivers/input/keyboard/keyboard.h"

#include "pic/pic.h"

#include "global/defines.h"

#include "libs/ttui/ttui.h"

// initialize the user level space
void initialize_system(void)
{
	tty_clear();
	print("Hello, Userspace!\n");
	// initializes a custom text based UI
	ttui_initialize(VGA_COLOR_WHITE, VGA_COLOR_CYAN);
	// creates a sidebar
	// 10 entries wide
	// empty separator (and connecting separator)
	// black foreground
	// dark gray background
	ttui_create_sidebar(10, ' ', ' ', VGA_COLOR_BLACK, VGA_COLOR_DARK_GRAY);
	// creates a title bar
	// contains the specified text
	// empty separator
	// 3 rows high
	// black foreground
	// light gray background
	ttui_create_title(
		"Hallo Welt! Hello World! Hola Mundo!",
		' ',
		3,
		VGA_COLOR_BLACK,
		VGA_COLOR_LIGHT_GRAY);
	// entries to be created in the main block
	ttui_write_to_main_block(
		"hello guys, this is my first operating system and kernel and this "
		"took me ~1 month and 1000 lines of code");
	ttui_write_to_main_block("i wrote this myself");
	ttui_write_to_main_block("this is my best project so far");
}
