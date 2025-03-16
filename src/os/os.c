#include "drivers/tty/tty.h"

#include "libs/stdout/stdout.h"

#include "drivers/input/keyboard/keyboard.h"

#include "pic/pic.h"

#include "global/defines.h"

// initialize the user level space
void initialize_system(void) { tty_clear(); }
