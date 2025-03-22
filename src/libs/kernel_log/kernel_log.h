#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

// log a message from the kernel
// arguments:
//	  - type - what kind of message it is
//			 - 0 is a success
//			 - 1 is an error
//			 - 2 is a warning
//			 - 3 is an info
//	  - *message - string containing the message to log
void kernel_log(int type, const char *message);

#endif
