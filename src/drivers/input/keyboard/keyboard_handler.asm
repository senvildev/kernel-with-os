.extern keyboard_handler	  # get the C keyboard handler function
.global keyboard_handler_asm  # declare the function as global

# create a function that calls the
# C keyboard handler
keyboard_handler_asm:
	call keyboard_handler	  #	invoke the C keyboard handler
	iret					  # return from the interrupt
