#include <stddef.h>
#include <stdint.h>

#include "vga_text.h"
#include "libs/string/string.h"

size_t vga_text_row = 0;
size_t vga_text_column = 0;

uint8_t vga_text_color;
uint16_t *vga_text_buffer = (uint16_t *)0xb8000;

// initialize the vga_text
void vga_text_initialize(void)
{
	// set the row and column to 0 (start on upper left corner)
	vga_text_row = 0;
	vga_text_column = 0;
	// set its color to light gray text on a black background
	vga_text_color = vga_entry_color(VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLACK);
	// loop through all the screen coordinates
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			// get the index of the vga_text buffer
			const size_t index = y * VGA_WIDTH + x;
			// set it to an empty character with the above color
			vga_text_buffer[index] = vga_entry(' ', vga_text_color);
		}
}

// clear the entire vga_text
void vga_text_clear(void)
{
	// start from the upper left corner
	vga_text_row = 0;
	vga_text_column = 0;
	// loop through all the coordinates
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			// get the index of the vga_text buffer
			const size_t index = y * VGA_WIDTH + x;
			// set it to an empty character with the color
			vga_text_buffer[index] = vga_entry(' ', vga_text_color);
		}
}

// insert a character on a specific coordinate on the vga_text
void vga_text_insert_entry_at(const char character, size_t x, size_t y)
{
	// get the index on the vga_text
	const size_t index = y * VGA_WIDTH + x;
	// insert the character to the buffer
	vga_text_buffer[index] = vga_entry(character, vga_text_color);
}

// insert a character on the vga_text
void vga_text_insert_entry(const char character)
{
	// insert it on the current X and Y coordinate
	vga_text_insert_entry_at(character, vga_text_column, vga_text_row);
	// add +1 to the X coordinate
	// check the X coordinate surpasses the width
	if (++vga_text_column == VGA_WIDTH)
	{
		// go back to the 0 X coordinate
		vga_text_column = 0;
		// add +1 to the Y coordinate
		if (++vga_text_row == VGA_HEIGHT)
			// go back to the 0 Y coordinate
			vga_text_row = 0;
	}
}

// write a set of characters to the vga_text (loop)
void vga_text_write(const char *data, size_t size)
{
	// for the entire length of the set of characters
	for (size_t i = 0; i < size; i++)
		// insert the character
		vga_text_insert_entry(data[i]);
}

// write a set of characters (main)
void vga_text_write_string(const char *data)
{
	// get the length of the passed set
	// pass the set to the function below
	vga_text_write(data, strlen(data));
	// create a newline
	vga_text_row++;
	vga_text_column = 0;
}
