.section .text
.global protected_mode_switch
.type protected_mode_switch, @function

.extern protected_kernel_main

protected_mode_switch:
    movl %cr0, %eax		  # get the protected mode bit
    orl $1, %eax		  # change it to 1
    movl %eax, %cr0		  # set the protected mode bit to 1
    
	ljmp $0x08, $flush	  # jump to flush

flush:
    movw $0x10, %ax     # 0x10 is the data segment selector
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
	# jump to the protected kernel function
    call protected_kernel_main 
    # just in case
    hlt
