.global isr0

isr0:
	cli
	push 0
	push 0
	call isr_0
	iret
