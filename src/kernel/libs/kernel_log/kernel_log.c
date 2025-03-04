#include "libs/string/string.h"
#include "libs/stdout/stdout.h"

#include "kernel_log.h"

const char *kernel_log_text[4] = {
	"kernel: success: ",
	"kernel: error: ",
	"kernel: warning: ",
	"kernel: info: "};

void kernel_log(int type, const char *message)
{
	if (type < 0 && type > 3)
		return;

	char *full_message = (char *)kernel_log_text[type];
	strcat(full_message, message);
	printn(full_message);
}
