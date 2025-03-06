#include <stdint.h>

char *addr_to_string(char *buffer, uintptr_t addr)
{
	const char hex_digits[] = "0123456789ABCDEF";

	// Add "0x" prefix
	buffer[0] = '0';
	buffer[1] = 'x';

	// Process address 4 bits at a time, from most significant to least
	for (int i = 0; i < sizeof(uintptr_t) * 2; i++)
	{
		// Extract 4 bits (a hex digit) starting from the most significant
		int shift = (sizeof(uintptr_t) * 8) - 4 - (i * 4);
		int digit;

		if (shift < 0)
		{
			// Handle architectures where sizeof(uintptr_t)*2 isn't a multiple
			// of 4
			digit = addr & 0xF;
		}
		else
		{
			digit = (addr >> shift) & 0xF;
		}

		// Convert to ASCII and store
		buffer[i + 2] = hex_digits[digit];
	}

	// Null terminate the string
	buffer[sizeof(uintptr_t) * 2 + 2] = '\0';

	return buffer;
}
