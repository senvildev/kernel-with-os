.section .text
# mark the switch function as global
.global protected_mode_switch
# define its type
.type protected_mode_switch, @function

# get the external protected kernel function
.extern protected_kernel_main

protected_mode_switch:
    movl %cr0, %eax		  # get the protected mode bit in control register 0
    orl $1, %eax		  # change it to 1
    movl %eax, %cr0		  # set the protected mode bit to 1
    
	ljmp $0x08, $flush	  # jump to flush

flush:
    movw $0x10, %ax		  # load the data segment selector to the AX register
    movw %ax, %ds		  # set the data segment to the value in AX
    movw %ax, %es		  # set the	extra segment to the value in AX
    movw %ax, %fs		  # set the extra segment to the value in AX
    movw %ax, %gs		  # set the extra segment to the value in AX
    movw %ax, %ss		  # set the stack segment to the value in AX
	# jump to the protected kernel function
    call protected_kernel_main 
    # just in case
    hlt
