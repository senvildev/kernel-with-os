#include <stdint.h>

#include "conversions.h"

char *addr_to_string(char *buffer, uintptr_t address)
{
	// add "0x" prefix
	buffer[0] = '0';
	buffer[1] = 'x';

	// process address 4 bits at a time, from most significant to least
	for (int i = 0; i < sizeof(uintptr_t) * 2; i++)
	{
		// extract 4 bits (a hex digit) starting from the most significant
		int shift = (sizeof(uintptr_t) * 8) - 4 - (i * 4);
		int digit;

		if (shift < 0)
			// handle architectures where sizeof(uintptr_t)*2 isn't a multiple
			// of 4
			digit = address & 0xF;
		else
			digit = (address >> shift) & 0xF;

		// Convert to ASCII and store
		buffer[i + 2] = HEX_DIGITS[digit];
	}

	// null terminate the string
	buffer[sizeof(uintptr_t) * 2 + 2] = '\0';
	// return the buffer
	return buffer;
}
