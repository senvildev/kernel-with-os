#include <stddef.h>

#include "libs/string/string.h"

// function that connects 2 strings together
char *strcat(char *destination_text, const char *text_to_add)
{
	size_t i, j;

	static char buffer[1024];

	for (i = 0; destination_text[i] != '\0'; i++)
		buffer[i] = destination_text[i];

	for (j = 0; text_to_add[j] != '\0'; j++)
		buffer[i + j] = text_to_add[j];
	buffer[i + j] = '\0';

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
