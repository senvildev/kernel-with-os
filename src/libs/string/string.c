#include <stddef.h>

#include "libs/string/string.h"

// function that connects 2 strings together
char *strcat(char *destination_text, const char *text_to_add)
{
	// create characters to store string sizes
	size_t i, j;
	// create a buffer with a 1024 character limit
	static char buffer[1024];
	// for each character in destination text
	for (i = 0; destination_text[i] != '\0'; i++)
		buffer[i] = destination_text[i]; // add character to text buffer
	// for each character in text to add
	for (j = 0; text_to_add[j] != '\0'; j++)
		buffer[i + j] = text_to_add[j]; // add character to text buffer
	buffer[i + j] = '\0';				// end with a null terminator
	// return the string
	return buffer;
};

// gets the length of passed string
size_t strlen(const char *str)
{
	size_t len = 0; // initialize length
	// add 1 as long as the character exists OR is valid (not code 0)
	while (str[len] || str[len] != 0)
		len++;
	return len; // return the length
}
