.section .text

.macro ISR_STUB num			# create a macro for ISR stubs listed below
.global isr\num				# define it as global (available to the code)
.extern handle_isr\num		# import an external handle for the ISR
isr\num:
    cli						# stop any ongoing interrupts
    pushal					# push all general purpose registers to the stack
    cld						# ensure string operations go forward
    call handle_isr\num		# call the ISR handler
    popal					# restore general purpose registers
    sti						# resume interrupts
    iret					# return from the interrupts
.endm						# end the macro

.macro ISR_STUB_WITH_ERROR num	  # create a macro for each stub that has an error message
.global isr\num				# make it global (available to the code)
.extern handle_isr\num		# import an external handle for the ISR
isr\num:
    cli						# stop ongoing interrupts
    pushal					# push all general purpose registers to the stack
    cld						# ensure string operations go forward
    call handle_isr\num		# call the ISR handler
    popal					# restore the general purpose registers
    addl $4, %esp			# adjust the stack pointer to remove the error code
    sti						# resume interrupts
	iret					# return from the interrupt
.endm						# end the macro

.global isr_default			# create a global default ISR handler
.extern handle_isr_default	# get the external handle function
isr_default:
    cli						# stop any interrupts
    pushal					# push all general purpose registers to the stack
    cld						#
    call handle_isr_default	# call the default handle function
    popal					# restore the general purpose registers to the stack
    sti						# resume interrupts
    iret					#

ISR_STUB 0					# division by zero
ISR_STUB 1					# debug exception
ISR_STUB 2					# non-maskable interrupt
ISR_STUB 3					# breakpoint
ISR_STUB 4					# overflow
ISR_STUB 5					# bound range exceeded
ISR_STUB 6					# invalid opcode
ISR_STUB 7					# device not available
ISR_STUB_WITH_ERROR 8		# double fault
ISR_STUB 9					# coprocessor segment overrun
ISR_STUB_WITH_ERROR 10		# invalid TSS
ISR_STUB_WITH_ERROR 11		# segment not present
ISR_STUB_WITH_ERROR 12		# stack-segment fault
ISR_STUB_WITH_ERROR 13		# general protection fault
ISR_STUB_WITH_ERROR 14		# page fault
ISR_STUB 15					# reserved
ISR_STUB 16					# x87 floating-point exception
ISR_STUB_WITH_ERROR 17		# alignment check
ISR_STUB 18					# machine check
ISR_STUB 19					# SIMD floating-point exception
ISR_STUB 20					# virtualization exception
ISR_STUB 21					# control protection exception
ISR_STUB 22					# reserved
ISR_STUB 23					# reserved
ISR_STUB 24					# reserved
ISR_STUB 25					# reserved
ISR_STUB 26					# reserved
ISR_STUB 27					# reserved
ISR_STUB 28					# reserved
ISR_STUB 29					# reserved
ISR_STUB 30					# security exception
ISR_STUB 31					# reserved
