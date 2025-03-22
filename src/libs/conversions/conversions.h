#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <stdint.h>

// list of hexadecimal characters
extern const char HEX_DIGITS[];

// function that turns a hexadecimal
// address into a string.
// arguments:
//	  - *buffer - buffer to store the string in
//	  - address - address to conver to string
char *address_to_string(char *buffer, uintptr_t address);

#endif
