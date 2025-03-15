#include <stdint.h>

#ifndef PIC_H
#define PIC_H

// define ports for the PIC
//	  - intel 8259 PIC chips come in a
//		master/slave setup
#define MASTER_PIC_COMMAND_PORT 0x20
#define MASTER_PIC_DATA_PORT 0x21
#define SLAVE_PIC_COMMAND_PORT 0xA0
#define SLAVE_PIC_DATA_PORT 0xA1

// define ICW1 (Initialization Command Word) bits
//	  - documented inside the Intel
//		8259A datasheet

// ICW4 follow-up
//	  - if set to 1	- ICW4 will be sent after ICW3
//	  - if set to 0 - ICW4 wont be sent and will stop
//					  on ICW3
#define ICW1_ICW4 0x01

// single mode
//	  - if set to 1	- the PIC will operate as a standalone
//					  controller
//	  - if set to 0 - the PIC will operate as a part of
//	  -				  a cascaded configuration (IRQ2 used
//					  as the connection)
#define ICW1_SINGLE_MODE 0x02

// call address interval
//	  - if set to 1 - the interrupt vectors are 8 bits apart
//					  (for the 8080/8085 architecture)
//	  - if set to 0 - the interrupt vectors are 4 bits apart
//					  (for the 8086/8088 architecture)
#define ICW1_INTERVAL4 0x04

// trigger mode
//	  - if set to 1 - level-triggered mode; the PIC detects
//					  the interrupt if its on high voltage
//	  - if set to 0 - edge-triggered mode; the PIC detects
//					  the interrupt on the rising edge of
//					  the signal (when the signal goes from
//					  low voltage to high voltage)
#define ICW1_LEVEL 0x08

// initialization mode
//	  - if set to 1 - signals the PIC that the initialization
//					  is beginning
#define ICW1_INIT 0x10

// define ICW4

// processor mode
//	  - if set to 1 - the PIC operates in 8086 mode
//					  (suitable for 8086/8088 and x86
//					  processors)
//	  - if set to 0 - the PIC operates in MCS-80/85 mode
//					  (suitable for 8080/8085 processors)
#define ICW4_8086 0x01

// auto end-of-interrupt
//	  - if set to 1 - auto-EOI mode; the PIC automatically
//					  issues an EOI at the end of the interrupt
//					  acknowledge cycle (no need for a software
//					  explicit EOI command)
//	  - if set to 0 - normal EOI mode; the ISR must send an explicit
//					  signal with an EOI command when it finishes
//					  processing the interrupt
#define ICW4_AUTO 0x02

// buffered mode
//	  - if both set to 0	- non-buffered mode; the PIC directly
//							  drives the interrupt signals
//	  - if slave set to 1	- buffered mode as a slave; the PIC's
//							  output is buffered and it acts as a
//							  slave
//	  - if master set to 1	- buffered mode as master; the PIC's
//							  output is buffered and it acts as a
//							  master
#define ICW4_BUFFER_SLAVE 0x08
#define ICW4_BUFFER_MASTER 0x0C

// special fully nested mode
//	  - if set to 1 - special fully nested mode; the master PIC
//					  allows higher priority interrupts from the
//					  slave PIC, even if it's currently processing
//					  an interrupt from the slave
//	  - if set to 0 - normal nested mode; when processing an interrupt
//					  from the slave PIC, the master won't notice
//					  higher priority interrupts from the same slave
//					  until the current one is complete
#define ICW4_SFNM 0x10

#endif

// function that creates a delay between
// input/output operations in the PIC
//	  it writes 0 to port 0x80 using the outb
//	  instruction. writing to this port takes a
//	  small amount of time, creating a delay
static inline void io_wait(void)
{
	__asm__ volatile("outb %%al, $0x80" : : "a"(0));
}

// function that reads a byte from a specified
// input/output port
// arguments:
//	  - port  - 16 bit (0x00) port address
//				to read from
static inline uint8_t inb(uint16_t port)
{
	uint8_t byte;
	// read a byte from the specified address and
	// write it to the variable
	__asm__ volatile("inb %1, %0" : "=a"(byte) : "Nd"(port));
	return byte;
}

// function that writes a byte to a specified
// input/output port
// arguments:
//	  - port  - 16 bit (0x00) port address
//	  - value - 8 bit (1 byte) value to write
static inline void outb(uint16_t port, uint8_t value)
{
	// write the byte to a specified
	// 16 bit address
	__asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void pic_setup(void);

// function that enables a specific
// IRQ in the PIC
// arguments:
//	  - irq	  - number of the IRQ (0-15)
void pic_enable_irq(uint8_t irq);

// straightforward function that enables
// all the IRQ's in the PIC
void pic_enable_all_irqs(void);

// sends end of interrupt signal to the PIC
void pic_send_eoi(uint8_t irq);

void pic_disable_irq(uint8_t irq);
void pic_disable_all_irqs(void);
