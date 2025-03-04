#include "libs/string/string.h"

// function that connects 2 strings together
void strcat(char *destination_text, const char *text_to_add)
{
	// while the destination text isnt on the end
	while (*destination_text != '\0')
		// move the cursor 1 place (left to right)
		destination_text++;

	// while the text to add isnt on the end
	while (*text_to_add != '\0')
	{
		// set the current empty place in destination_text
		// to the current character in the text to be added
		*destination_text = *text_to_add;
		// move both cursors 1 place to the right
		destination_text++;
		text_to_add++;
	}
	// end the string with an empty character
	*destination_text = '\0';
};
