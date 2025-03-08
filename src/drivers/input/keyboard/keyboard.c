#include <stdint.h>

#include "keyboard.h"

uint8_t kb_get_scancode(uint16_t port)
{
	uint8_t result;
	// assembly code to get keyboard input scancode
	__asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
	// return scancode
	return result;
}
