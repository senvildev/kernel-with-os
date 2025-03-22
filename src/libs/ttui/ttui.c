#include "drivers/bios_vga/bios_vga.h"
#include "libs/string/string.h"

// set UI manipulation
// variables to defaults
int SIDEBAR_WIDTH = 0;
int MAIN_BLOCK_NEXT_ELEMENT_ROW = 0;

// set default color variables
// to the default values
enum VGA_COLOR default_color_foreground = VGA_COLOR_LIGHT_GRAY;
enum VGA_COLOR default_color_background = VGA_COLOR_BLACK;

// resets the BIOS VGA color to defaults
// in case it has been changed
void reset_bios_vga_color(void)
{
	bios_vga_color =
		vga_entry_color(default_color_foreground, default_color_background);
}

// selects between color1 and color2
// returns color2 if the color1 is the default color
enum VGA_COLOR select_color(enum VGA_COLOR color1, enum VGA_COLOR color2)
{
	// does a check and returns based on the data
	return (color1 == VGA_COLOR_DEFAULT) ? color2 : color1;
}

// writes text to the main block
void ttui_write_to_main_block(char *text)
{
	// sets the BIOS VGA row on the
	// next main block element
	bios_vga_row = MAIN_BLOCK_NEXT_ELEMENT_ROW;
	// sets the BIOS VGA column on the end of
	// the sidebar + 1 space margin
	bios_vga_column = SIDEBAR_WIDTH + 2;
	// iterates through each character
	for (int i = 0; i < strlen(text); i++)
	{
		// gets the single character
		const char character = text[i];
		// if the column is on the end - 1 space
		if (bios_vga_column >= VGA_WIDTH - 1)
		{
			// sets the BIOS VGA column on the
			// end of the sidebar + 1 margin
			bios_vga_column = SIDEBAR_WIDTH + 2;
			// goes to the next row
			bios_vga_row++;
		}
		// inserts the character
		bios_vga_insert_entry(character);
	}
	// sets the next row for another antry as:
	// 2 places lower, so current row + 1 margin
	MAIN_BLOCK_NEXT_ELEMENT_ROW = bios_vga_row + 2;

	// resets the default color of the
	// cursor
	reset_bios_vga_color();
}

// creates a titlebar
void ttui_create_title(
	char *text,
	char separator,
	int height,
	enum VGA_COLOR foreground,
	enum VGA_COLOR background)
{
	// checks if the height is correct
	if (height <= 1)
		return; // stops the function if it isn't

	// chooses between default or passed color
	// based on the passed arguments
	foreground = select_color(foreground, default_color_foreground);
	background = select_color(background, default_color_background);
	// sets the colors on the BIOS VGA
	bios_vga_color = vga_entry_color(foreground, background);

	// goes through each row of the height
	for (int row = 0; row < height; row++)
	{
		// sets the current BIOS VGA row to the
		// iterating row variable
		bios_vga_row = row;
		// goes through each column
		// (except for what the sidebar is occupying)
		for (int column = SIDEBAR_WIDTH; column < VGA_WIDTH; column++)
		{
			// sets the BIOS VGA column to the
			// iterating column variable
			bios_vga_column = column;
			// sets the current cursor placement
			// to an empty character
			bios_vga_insert_entry(' ');
		}
	}

	// calculate where to start placing text
	// to make it centered
	int starting_column = (VGA_WIDTH + SIDEBAR_WIDTH - strlen(text)) / 2;
	// set the BIOS VGA cursor column to the
	// calculated text start
	bios_vga_column = starting_column;
	// get the center of the height
	int text_row = (height / 2);
	if (height % 2 == 0)
		// lower the text row by 1 if
		// the height is even
		text_row--;
	// set the BIOS VGA row cursor to the
	// height center
	bios_vga_row = text_row;
	// write the passed text
	bios_vga_write_string(text);

	// sets the BIOS VGA row cursor to the
	// lowest place on the height
	bios_vga_row = height - 1;
	// iterate through each column
	for (int column = SIDEBAR_WIDTH; column < VGA_WIDTH; column++)
	{
		// set the BIOS VGA column cursor to
		// the current iterated column
		bios_vga_column = column;
		// set the separator character
		bios_vga_insert_entry(separator);
	}

	// set the main block element row
	// start to the height with a single
	// row of margin
	MAIN_BLOCK_NEXT_ELEMENT_ROW = height + 1;

	// reset the BIOS VGA color to default
	reset_bios_vga_color();
}

// creates a sidebar
void ttui_create_sidebar(
	int width,
	char separator,
	char connected_separator,
	enum VGA_COLOR foreground,
	enum VGA_COLOR background)
{
	// sets the sidebar width to the
	// passed width parameter
	SIDEBAR_WIDTH = width;
	// chooses the colors based on the
	// passed arguments
	foreground = select_color(foreground, default_color_foreground);
	background = select_color(background, default_color_background);
	// sets the BIOS VGA color to the selected
	// colors
	bios_vga_color = vga_entry_color(foreground, background);
	// loop through each row in the BIOS VGA
	for (int row = 0; row < VGA_HEIGHT + 1; row++)
	{
		// loop through each column for the
		// width of the sidebar
		for (int column = 0; column < SIDEBAR_WIDTH; column++)
		{
			// sets the BIOS VGA column to the
			// currently iterated column
			bios_vga_column = column;
			// sets a separator character if it is
			// on the end of the sidebar
			// otherwise sets an empty character
			if (column == SIDEBAR_WIDTH - 1)
				bios_vga_insert_entry(separator);
			else
				bios_vga_insert_entry(' ');
		}
		// sets the BIOS VGA row to the
		// currently iterating row
		bios_vga_row = row;

		// commented out since i need
		// to improve this part of code
		//
		// if (i == 1)
		//	bios_vga_insert_entry(connected_separator);
		//	else
		//		bios_vga_insert_entry(separator);
	}

	// resets the BIOS VGA buffer color
	reset_bios_vga_color();
}

// initializes the TTUI library
void ttui_initialize(enum VGA_COLOR foreground, enum VGA_COLOR background)
{
	// checks for new default passed colors
	if (foreground != VGA_COLOR_DEFAULT)
		default_color_foreground = foreground;
	if (background != VGA_COLOR_DEFAULT)
		default_color_background = background;

	// sets the color
	bios_vga_color =
		vga_entry_color(default_color_foreground, default_color_background);
	// clears the BIOS VGA with the color
	bios_vga_clear();
}
