#include "libs/string/string.h"

char *strcat(char *destination_text, const char *text_to_add)
{
	while (*destination_text != '\0')
		destination_text++;

	while (*text_to_add != '\0')
	{
		*destination_text = *text_to_add;
		destination_text++;
		text_to_add++;
	}

	*destination_text = '\0';

	return destination_text;
};
