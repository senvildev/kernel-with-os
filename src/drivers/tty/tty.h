#include <stddef.h>
#include <stdint.h>

// TTY macro
#ifndef TTY_H
#define TTY_H

#define VGA_WIDTH 80  // width of the screen
#define VGA_HEIGHT 25 // height of the screen

// coordinate variables
extern size_t tty_column; // x coordinate
extern size_t tty_row;	  // u coordinate

// variable storing TTY VGA color
extern uint8_t tty_color;

// variable storing the VGA screen buffer
extern uint16_t *tty_buffer;

#endif

// enumerator of colors
// names say enough
enum VGA_COLORS
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GRAY = 7,
	VGA_COLOR_DARK_GRAY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

// create the VGA color data
// arguments:
//	  - foreground - text color
//	  - background - background color
static inline uint8_t
vga_entry_color(enum VGA_COLORS foreground, enum VGA_COLORS background)
{
	return foreground | background << 4;
}

// returns data for a character with a color on the screen
// arguments:
//	  - character - the sign to place
//	  - color - color (from vga_entry_color)
static inline uint16_t vga_entry(unsigned char character, uint8_t color)
{
	return (uint16_t)character | (uint16_t)color << 8;
}

// initialize the TTY with a blank screen
void tty_initialize(void);

// clear the entire TTY
void tty_clear(void);

// insert a character at a specific coordinate on the TTY
// arguments:
//	  - character - the character to insert
//	  - x - TTY column (x coordinate)
//	  - y - TTY row (y coordinate)
void tty_insert_entry_at(const char character, size_t x, size_t y);

// insert a character on the TTY
// arguments:
//	  - character - the character to insert
void tty_insert_entry(const char character);

// write a set of characters to the TTY (loop)
// arguments:
//	  - *data - set of characters to write
//	  - size - length of the set
void tty_write(const char *data, size_t size);

// write a set of characters to the TTY (main)
// arguments:
//	  - *data - set of characters to write
void tty_write_string(const char *data);
