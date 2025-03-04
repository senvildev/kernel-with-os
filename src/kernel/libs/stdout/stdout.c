#include "tty/tty.h"

#include "stdout.h"

void print(char *message)
{
	int i = 0;
	char character;
	while (message[i] != '\0')
	{
		character = message[i];
		if (character == '\n')
		{
			tty_row++;
			tty_column = 0;
		}
		else
			tty_insert_entry(message[i]);

		i++;
	}
}

void printn(char *message)
{
	print(message);
	tty_row++;
	tty_column = 0;
}
