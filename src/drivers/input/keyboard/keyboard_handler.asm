.extern keyboard_handler
.global keyboard_handler_asm

keyboard_handler_asm:
	cli
	pushal
	cld
	call keyboard_handler
	popal
	sti
	iret
