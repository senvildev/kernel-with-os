#include <stddef.h>

#ifndef STRING_H
#define STRING_H

#endif

// concatenate 2 strings together
// arguments:
//	  - destination_text - string that contains the text to be added to
//	  - text_to_add - text to add
// the result is returned as a string
char *strcat(char *destination_text, const char *text_to_add);

// returns the length of a passed string/set of characters
// arguments:
//	  - str - string/set of characters
size_t strlen(const char *str);
