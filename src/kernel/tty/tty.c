#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "libs/string/string.h"

size_t tty_row = 0;
size_t tty_column = 0;

uint8_t tty_color;
uint16_t *tty_buffer = (uint16_t *)0xb8000;

// initialize the TTY
void tty_initialize(void)
{
	// set the row and column to 0 (start on upper left corner)
	tty_row = 0;
	tty_column = 0;
	// set its color to light gray text on a black background
	tty_color = vga_entry_color(VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLACK);
	// loop through all the screen coordinates
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			// get the index of the tty buffer
			const size_t index = y * VGA_WIDTH + x;
			// set it to an empty character with the above color
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
}

// clear the entire TTY
void tty_clear(void)
{
	// start from the upper left corner
	tty_row = 0;
	tty_column = 0;
	// loop through all the coordinates
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			// get the index of the TTY buffer
			const size_t index = y * VGA_WIDTH + x;
			// set it to an empty character with the color
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
}

// insert a character on a specific coordinate on the TTY
void tty_insert_entry_at(const char character, size_t x, size_t y)
{
	// get the index on the TTY
	const size_t index = y * VGA_WIDTH + x;
	// insert the character to the buffer
	tty_buffer[index] = vga_entry(character, tty_color);
}

// insert a character on the TTY
void tty_insert_entry(const char character)
{
	// insert it on the current X and Y coordinate
	tty_insert_entry_at(character, tty_column, tty_row);
	// add +1 to the X coordinate
	// check the X coordinate surpasses the width
	if (++tty_column == VGA_WIDTH)
	{
		// go back to the 0 X coordinate
		tty_column = 0;
		// add +1 to the Y coordinate
		if (++tty_row == VGA_HEIGHT)
			// go back to the 0 Y coordinate
			tty_row = 0;
	}
}

// write a set of characters to the TTY (loop)
void tty_write(const char *data, size_t size)
{
	// for the entire length of the set of characters
	for (size_t i = 0; i < size; i++)
		// insert the character
		tty_insert_entry(data[i]);
}

// write a set of characters (main)
void tty_write_string(const char *data)
{
	// get the length of the passed set
	// pass the set to the function below
	tty_write(data, strlen(data));
}
