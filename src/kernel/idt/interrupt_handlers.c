#include "libs/kernel_log/kernel_log.h"

extern void isr0(void);

extern void isr_0(void)
{
	kernel_log(1, "whoops! divided by 0!");
	while (1)
		;
}
