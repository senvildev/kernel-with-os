#include "drivers/tty/tty.h"
#include "libs/string/string.h"

// set UI manipulation
// variables to defaults
int SIDEBAR_WIDTH = 0;
int MAIN_BLOCK_NEXT_ELEMENT_ROW = 0;

// set default color variables
// to the default values
enum VGA_COLORS default_color_foreground = VGA_COLOR_LIGHT_GRAY;
enum VGA_COLORS default_color_background = VGA_COLOR_BLACK;

// resets the TTY color to defaults
// in case it has been changed
void reset_tty_color(void)
{
	tty_color =
		vga_entry_color(default_color_foreground, default_color_background);
}

// selects between color1 and color2
// returns color2 if the color1 is the default color
enum VGA_COLORS select_color(enum VGA_COLORS color1, enum VGA_COLORS color2)
{
	// does a check and returns based on the data
	return (color1 == VGA_COLOR_DEFAULT) ? color2 : color1;
}

// writes text to the main block
void ttui_write_to_main_block(char *text)
{
	// sets the TTY row on the
	// next main block element
	tty_row = MAIN_BLOCK_NEXT_ELEMENT_ROW;
	// sets the TTY column on the end of
	// the sidebar + 1 space margin
	tty_column = SIDEBAR_WIDTH + 2;
	// iterates through each character
	for (int i = 0; i < strlen(text); i++)
	{
		// gets the single character
		const char character = text[i];
		// if the column is on the end - 1 space
		if (tty_column >= VGA_WIDTH - 1)
		{
			// sets the TTY column on the
			// end of the sidebar + 1 margin
			tty_column = SIDEBAR_WIDTH + 2;
			// goes to the next row
			tty_row++;
		}
		// inserts the character
		tty_insert_entry(character);
	}
	// sets the next row for another antry as:
	// 2 places lower, so current row + 1 margin
	MAIN_BLOCK_NEXT_ELEMENT_ROW = tty_row + 2;

	// resets the default color of the
	// cursor
	reset_tty_color();
}

// creates a titlebar
void ttui_create_title(
	char *text,
	char separator,
	int height,
	enum VGA_COLORS foreground,
	enum VGA_COLORS background)
{
	// checks if the height is correct
	if (height <= 1)
		return; // stops the function if it isn't

	// chooses between default or passed color
	// based on the passed arguments
	foreground = select_color(foreground, default_color_foreground);
	background = select_color(background, default_color_background);
	// sets the colors on the TTY
	tty_color = vga_entry_color(foreground, background);

	// goes through each row of the height
	for (int row = 0; row < height; row++)
	{
		// sets the current TTY row to the
		// iterating row variable
		tty_row = row;
		// goes through each column
		// (except for what the sidebar is occupying)
		for (int column = SIDEBAR_WIDTH; column < VGA_WIDTH; column++)
		{
			// sets the TTY column to the
			// iterating column variable
			tty_column = column;
			// sets the current cursor placement
			// to an empty character
			tty_insert_entry(' ');
		}
	}

	// calculate where to start placing text
	// to make it centered
	int starting_column = (VGA_WIDTH + SIDEBAR_WIDTH - strlen(text)) / 2;
	// set the TTY cursor column to the
	// calculated text start
	tty_column = starting_column;
	// get the center of the height
	int text_row = (height / 2);
	if (height % 2 == 0)
		// lower the text row by 1 if
		// the height is even
		text_row--;
	// set the TTY row cursor to the
	// height center
	tty_row = text_row;
	// write the passed text
	tty_write_string(text);

	// sets the TTY row cursor to the
	// lowest place on the height
	tty_row = height - 1;
	// iterate through each column
	for (int column = SIDEBAR_WIDTH; column < VGA_WIDTH; column++)
	{
		// set the TTY column cursor to
		// the current iterated column
		tty_column = column;
		// set the separator character
		tty_insert_entry(separator);
	}

	// set the main block element row
	// start to the height with a single
	// row of margin
	MAIN_BLOCK_NEXT_ELEMENT_ROW = height + 1;

	// reset the TTY color to default
	reset_tty_color();
}

// creates a sidebar
void ttui_create_sidebar(
	int width,
	char separator,
	char connected_separator,
	enum VGA_COLORS foreground,
	enum VGA_COLORS background)
{
	// sets the sidebar width to the
	// passed width parameter
	SIDEBAR_WIDTH = width;
	// chooses the colors based on the
	// passed arguments
	foreground = select_color(foreground, default_color_foreground);
	background = select_color(background, default_color_background);
	// sets the TTY color to the selected
	// colors
	tty_color = vga_entry_color(foreground, background);
	// loop through each row in the TTY
	for (int row = 0; row < VGA_HEIGHT + 1; row++)
	{
		// loop through each column for the
		// width of the sidebar
		for (int column = 0; column < SIDEBAR_WIDTH; column++)
		{
			// sets the TTY column to the
			// currently iterated column
			tty_column = column;
			// sets a separator character if it is
			// on the end of the sidebar
			// otherwise sets an empty character
			if (column == SIDEBAR_WIDTH - 1)
				tty_insert_entry(separator);
			else
				tty_insert_entry(' ');
		}
		// sets the TTY row to the
		// currently iterating row
		tty_row = row;

		// commented out since i need
		// to improve this part of code
		//
		// if (i == 1)
		//	tty_insert_entry(connected_separator);
		//	else
		//		tty_insert_entry(separator);
	}

	// resets the TTY buffer color
	reset_tty_color();
}

// initializes the TTUI library
void ttui_initialize(enum VGA_COLORS foreground, enum VGA_COLORS background)
{
	// checks for new default passed colors
	if (foreground != VGA_COLOR_DEFAULT)
		default_color_foreground = foreground;
	if (background != VGA_COLOR_DEFAULT)
		default_color_background = background;

	// sets the color
	tty_color =
		vga_entry_color(default_color_foreground, default_color_background);
	// clears the TTY with the color
	tty_clear();
}
