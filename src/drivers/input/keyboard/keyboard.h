#include <stdint.h>

// defines a type for keyboard callback functions
// consists of a pointer to the function
// arguments:
//	  - scan_code	- contains the scan code received
//					  from the keyboard controller
typedef void (*callback_function)(int scan_code);

#ifndef KEYBOARD_H
#define KEYBOARD_H

// defines the maximum amount of
// callbacks stored in the callback array
#define KEYBOARD_CALLBACK_LIMIT 256

// array that stores all callbacks that are there
extern callback_function keyboard_callbacks[KEYBOARD_CALLBACK_LIMIT];
// variable that stores the next index available
// for a new keyboard callback
extern int callbacks_next_index;

#endif

// registers a callback by adding it to the
// keyboard_callbacks array
// arguments:
//	  - callback	- contains the function that is called
//					  upon a key press
// returns the index of where the callback
// is stored in the array
int keyboard_register_callback(callback_function callback);
int keyboard_unregister_callback(int callback_id);

// C keyboard handler which invokes
// all callbacks stored in keyboard_callbacks.
// it runs upon any keypress
void keyboard_handler(void);

// function that initializes the keyboard
// by creating an entry in the IDT and
// attaching assembly code to it
void initialize_keyboard(void);
