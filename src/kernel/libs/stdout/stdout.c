#include "tty/tty.h"

#include "stdout.h"

// non-newline print function
void print(char *message)
{
	// define required variables
	int i = 0;
	char character;

	// loop until the passed string is real
	while (message[i] != '\0')
	{
		// set the current character
		character = message[i];
		// if the character is a newline
		if (character == '\n')
		{
			// do a newline
			tty_row++;
			tty_column = 0;
		}
		else // otherwise print the character to the screen
			tty_insert_entry(message[i]);
		// iterate through the loop further
		i++;
	}
}
