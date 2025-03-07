#include <stdint.h>

#ifndef CONVERSIONS_H
#define CONVERSIONS_H

// list of hexadecimal characters
const char HEX_DIGITS[] = "0123456789ABCDEF";

#endif

// function that turns a hexadecimal
// address into a string.
// arguments:
//	  - *buffer - buffer to store the string in
//	  - address - address to conver to string
char *address_to_string(char *buffer, uintptr_t address);
