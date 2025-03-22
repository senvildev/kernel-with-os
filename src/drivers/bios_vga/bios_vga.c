#include <stddef.h>
#include <stdint.h>

#include "bios_vga.h"
#include "libs/string/string.h"

size_t bios_vga_row = 0;
size_t bios_vga_column = 0;

uint8_t bios_vga_color;
uint16_t *bios_vga_buffer = (uint16_t *)0xb8000;

// initialize the bios_vga
void bios_vga_initialize(void)
{
	// set the row and column to 0 (start on upper left corner)
	bios_vga_row = 0;
	bios_vga_column = 0;
	// set its color to light gray text on a black background
	bios_vga_color = vga_entry_color(VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLACK);
	// loop through all the screen coordinates
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			// get the index of the bios_vga buffer
			const size_t index = y * VGA_WIDTH + x;
			// set it to an empty character with the above color
			bios_vga_buffer[index] = vga_entry(' ', bios_vga_color);
		}
}

// clear the entire bios_vga
void bios_vga_clear(void)
{
	// start from the upper left corner
	bios_vga_row = 0;
	bios_vga_column = 0;
	// loop through all the coordinates
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			// get the index of the bios_vga buffer
			const size_t index = y * VGA_WIDTH + x;
			// set it to an empty character with the color
			bios_vga_buffer[index] = vga_entry(' ', bios_vga_color);
		}
}

// insert a character on a specific coordinate on the bios_vga
void bios_vga_insert_entry_at(const char character, size_t x, size_t y)
{
	// get the index on the bios_vga
	const size_t index = y * VGA_WIDTH + x;
	// insert the character to the buffer
	bios_vga_buffer[index] = vga_entry(character, bios_vga_color);
}

// insert a character on the bios_vga
void bios_vga_insert_entry(const char character)
{
	// insert it on the current X and Y coordinate
	bios_vga_insert_entry_at(character, bios_vga_column, bios_vga_row);
	// add +1 to the X coordinate
	// check the X coordinate surpasses the width
	if (++bios_vga_column == VGA_WIDTH)
	{
		// go back to the 0 X coordinate
		bios_vga_column = 0;
		// add +1 to the Y coordinate
		if (++bios_vga_row == VGA_HEIGHT)
			// go back to the 0 Y coordinate
			bios_vga_row = 0;
	}
}

// write a set of characters to the bios_vga (loop)
void bios_vga_write(const char *data, size_t size)
{
	// for the entire length of the set of characters
	for (size_t i = 0; i < size; i++)
		// insert the character
		bios_vga_insert_entry(data[i]);
}

// write a set of characters (main)
void bios_vga_write_string(const char *data)
{
	// get the length of the passed set
	// pass the set to the function below
	bios_vga_write(data, strlen(data));
	// create a newline
	bios_vga_row++;
	bios_vga_column = 0;
}
