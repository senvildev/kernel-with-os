.section .text

.macro ISR_STUB num
.global isr\num
.extern handle_isr\num
isr\num:
    cli
    pushal
    cld
    call handle_isr\num
    popal
    sti
    iret
.endm

.macro ISR_STUB_WITH_ERROR num
.global isr\num
.extern handle_isr\num
isr\num:
    cli
    pushal
    cld
    call handle_isr\num
    popal
    sti
    add $4, %esp
	iret
.endm

.global isr_default
.extern handle_isr_default
isr_default:
    cli
    pushal
    cld
    call handle_isr_default
    popal
    sti
    iret

ISR_STUB 0    // Divide by Zero
ISR_STUB 1    // Debug Exception
ISR_STUB 2    // Non-maskable Interrupt
ISR_STUB 3    // Breakpoint
ISR_STUB 4    // Overflow
ISR_STUB 5    // Bound Range Exceeded
ISR_STUB 6    // Invalid Opcode
ISR_STUB 7    // Device Not Available
ISR_STUB_WITH_ERROR 8    // Double Fault
ISR_STUB 9    // Coprocessor Segment Overrun
ISR_STUB_WITH_ERROR 10   // Invalid TSS
ISR_STUB_WITH_ERROR 11   // Segment Not Present
ISR_STUB_WITH_ERROR 12   // Stack-Segment Fault
ISR_STUB_WITH_ERROR 13   // General Protection Fault
ISR_STUB_WITH_ERROR 14   // Page Fault
ISR_STUB 15   // Reserved
ISR_STUB 16   // x87 Floating-Point Exception
ISR_STUB_WITH_ERROR 17   // Alignment Check
ISR_STUB 18   // Machine Check
ISR_STUB 19   // SIMD Floating-Point Exception
ISR_STUB 20   // Virtualization Exception
ISR_STUB 21   // Control Protection Exception
ISR_STUB 22   // Reserved
ISR_STUB 23   // Reserved
ISR_STUB 24   // Reserved
ISR_STUB 25   // Reserved
ISR_STUB 26   // Reserved
ISR_STUB 27   // Reserved
ISR_STUB 28   // Reserved
ISR_STUB 29   // Reserved
ISR_STUB 30   // Security Exception
ISR_STUB 31   // Reserved
