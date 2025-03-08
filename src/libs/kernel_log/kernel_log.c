#include "libs/string/string.h"
#include "libs/stdout/stdout.h"

#include "kernel_log.h"

// table containing messages for logging kernel messages
const char *kernel_log_text[4] = {
	"kernel: success: ", // 0
	"kernel: error: ",	 // 1
	"kernel: warning: ", // 2
	"kernel: info: "};	 // 3

// log a kernel message
void kernel_log(int type, const char *message)
{
	// if incorrect type, stop code
	if (type < 0 || type > 3)
		return;
	// prepare the message to print
	char *full_message = (char *)kernel_log_text[type];
	// concatenate the prepared variable with the passed message
	full_message = strcat(full_message, message);
	full_message = strcat(full_message, "\n"); // add a newline
	// print the message to the screen
	print(full_message);
}
