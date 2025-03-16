#include <stdint.h>
#include <stddef.h>

#include "keyboard.h"

#include "pic/pic.h"
#include "idt/idt.h"

#include "drivers/tty/tty.h"

#include "libs/stdout/stdout.h"

#include "global/defines.h"

// these will be moved later on, storing these here for
// the time i need it to debug
const size_t CODES_PRESSED_SIZE = 59;
const char CODES_PRESSED[59] = {
	0,	 27,  '1',	'2',  '3',	'4', '5', '6',	'7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q',	'w', 'e', 'r',	't', 'y', 'u', 'i',
	'o', 'p', '[',	']',  '\n', 0,	 'a', 's',	'd', 'f', 'g', 'h',
	'j', 'k', 'l',	';',  '\'', '`', 0,	  '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm',	',',  '.',	'/', 0,	  0,	0,	 ' ', 0};

// get the assembly keyboard handler
extern void keyboard_handler_asm(void);

// creates an empty array for storing callbacks
callback_function keyboard_callbacks[KEYBOARD_CALLBACK_LIMIT];
// function that stores the next index available
// for the callback array
int callbacks_next_index = 0;

// creates the main keyboard handler
// in C (that sends a signal to all the callbacks)
void keyboard_handler(void)
{
	// gets the scan code from the
	// keyboard controller (IMPORTANT, REQUIRED!)
	int scan_code = inb(0x60);
	// check if the scan code is in range
	if (scan_code < CODES_PRESSED_SIZE)
	{
		// loop through all existing callbacks
		for (size_t i = 0; i < callbacks_next_index; i++)
		{
			// gets the callback from the array
			callback_function keyboard_callback = keyboard_callbacks[i];
			// checks if the keyboard callback exists
			if (keyboard_callback)
				// if it does, invoke it
				keyboard_callback(scan_code);
		};
	}
	// sends an EOI signal to the PIC
	// (IMPORTANT, REQUIRED!)
	pic_send_eoi(1);
}

// returns the index of the registered
// callback in the array
int keyboard_register_callback(callback_function callback)
{
	// checks if the next index isn't above
	// the maximum limit of callbacks
	if (callbacks_next_index >= KEYBOARD_CALLBACK_LIMIT)
		return FAILURE; // if it is, returns FAILURE
	// sets the callback in the callback array
	keyboard_callbacks[callbacks_next_index] = callback;
	// returns the index and adds 1 to it
	return callbacks_next_index++;
}

// returns whether unregistering the callback
// succeeded or not
int keyboard_unregister_callback(int callback_index)
{
	// checks if the passed callback index isn't
	// negative or isn't above the limit
	if (callbacks_next_index < 0 || callback_index >= KEYBOARD_CALLBACK_LIMIT)
		return FAILURE; // if it is, return FAILURE
	// for each index above until the (callback limit - 1)
	for (size_t i = callback_index; i < KEYBOARD_CALLBACK_LIMIT - 1; i++)
		// move every upper callback one place lower
		keyboard_callbacks[i] = keyboard_callbacks[i + 1];
	// sets the last callback to NULL
	keyboard_callbacks[KEYBOARD_CALLBACK_LIMIT - 1] = NULL;
	// reduce the next index by 1
	callbacks_next_index--;
	return SUCCESS; // returns SUCCESS
}

// function that initializes the keyboard
void initialize_keyboard(void)
{
	// load the assembly keyboard handler
	// into the IDT
	idt_set_entry(0x21, (uint32_t)(uintptr_t)keyboard_handler_asm, 0x08, 0x8E);
	// enable IRQ1 which is launched
	// upon any key press
	pic_enable_irq(1);
}
