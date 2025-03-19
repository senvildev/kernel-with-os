#include "global/defines.h"
#include "drivers/tty/tty.h"

#ifndef TTUI_H
#define TTUI_H

// variables holding UI
// manipulation data
extern int SIDEBAR_WIDTH;
extern int MAIN_BLOCK_NEXT_ELEMENT_ROW;

// variables holding the default colors
extern enum VGA_COLORS default_color_foreground;
extern enum VGA_COLORS default_color_background;

#endif

// writes text to the main block
// and creates an empty space below it
// arguments:
//	  - *text	  - character string for the content
void ttui_write_to_main_block(char *text);

// creates a titlebar on the top
// next to the sidebar
// arguments:
//	  - *text	  - character string for the content
//	  - separator - separator character (separates
//					the bottom of the titlebar)
//	  - height	  - height of the titlebar
//	  -	?foreground - text color of the titlebar
//	  - ?background - background color of the titlebar
//
// arguments marked with `?` will be replaced
// with values passed to the ttui_initialize
// function if you passed VGA_COLOR_DEFAULT
void ttui_create_title(
	char *text,
	char separator,
	int height,
	enum VGA_COLORS foreground,
	enum VGA_COLORS background);

// creates a sidebar on the left
// arguments:
//	  - width	  - width of the sidebar
//	  -	separator - separates the sidebar
//					from the right side of the screen
//	  - connected_separator - connects with titlebars
//							  separator
//	  - ?foreground - text color of the sidebar
//	  - ?background - background color of the sidebar
//
// arguments marked with `?` will be replaced
// with values passed to the ttui_initialize
// function if you passed VGA_COLOR_DEFAULT
void ttui_create_sidebar(
	int width,
	char separator,
	char connected_separator,
	enum VGA_COLORS foreground,
	enum VGA_COLORS background);

// initializes the TTUI interface
// arguments:
//	  - ?foreground - default text color
//	  - ?background - default background color
//
// arguments marked with `?` will be replaced
// with:
//	- foreground - VGA_COLOR_LIGHT_GRAY
//	- background - VGA_COLOR_BLACK
// if they received a VGA_COLOR_DEFAULT value
void ttui_initialize(enum VGA_COLORS foreground, enum VGA_COLORS background);
