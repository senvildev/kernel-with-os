#include <stdint.h>

#include "pic.h"

#include "libs/kernel_log/kernel_log.h"

// function to set up the entire PIC
void pic_setup(void)
{
	// the io_wait(); repetition is required
	// to ensure that the PIC has enough time
	// to write data

	kernel_log(3, "setting up the PIC");

	// start initialization sequence
	// sets bits for ICW1_ICW4 and ICW1_INIT
	// (ICW1_INIT is required for initialization)
	// cascade mode
	// 8 byte interrupt vector interval
	// edge-triggered mode
	outb(MASTER_PIC_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(SLAVE_PIC_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
	io_wait();

	// set vector offsets
	outb(MASTER_PIC_DATA_PORT, 0x20); // IRQ0 - IRQ7 start at 0x20
	io_wait();
	outb(SLAVE_PIC_DATA_PORT, 0x28); // IRQ8 - IRQ15 start at 0x28
	io_wait();

	// tell the master PIC about the slave PIC
	// 0b10 says that a slave is connected to IRQ2
	outb(MASTER_PIC_DATA_PORT, 4);
	io_wait();
	// value 2 tells the slave PIC its cascade
	// identity (that its connected by IRQ2 to
	// the master)
	outb(SLAVE_PIC_DATA_PORT, 2);
	io_wait();

	// set the mode for both PIC's
	// non auto-EOI
	// non-buffered mode
	// normal nested mode
	outb(MASTER_PIC_DATA_PORT, ICW4_8086);
	io_wait();
	outb(SLAVE_PIC_DATA_PORT, ICW4_8086);
	io_wait();

	// restore masks (and initially mask
	// all interrupts)
	// THIS DISABLES ALL INTERRUPTS!!!
	outb(MASTER_PIC_DATA_PORT, 0xFF);
	outb(SLAVE_PIC_DATA_PORT, 0xFF);

	kernel_log(0, "set up the PIC and disabled all IRQ's");
}

// function to enable a specific IRQ
// in the PIC
void pic_enable_irq(uint8_t irq)
{
	// check just in case the passed
	// IRQ doesn't match the limit
	if (irq > 15) // doesn't require a below zero check
		return;

	// declare required variables
	uint16_t pic_port; // port of the PIC
	uint8_t irq_mask;  // mask controlling which IRQ
					   // is enabled/disabled

	// check whether the IRQ is in the master
	// PIC or the slave PIC
	if (irq < 8)
		//
		pic_port = MASTER_PIC_DATA_PORT;
	else
	{
		pic_port = SLAVE_PIC_DATA_PORT;
		irq -= 8;
	}

	// get the IRQ mask byte
	irq_mask = inb(pic_port);
	// clear the IRQ mask (to enable it)
	irq_mask &= ~(1 << irq);

	// write the IRQ mask to
	// the PIC port
	outb(pic_port, irq_mask);
}

// function that enables all IRQ's
// in the PIC
void pic_enable_all_irqs(void)
{
	// loop through IRQ0 to IRQ15
	for (uint8_t i = 0; i < 16; i++)
		// enable the IRQ
		pic_enable_irq(i);
}

void pic_disable_irq(uint8_t irq)
{
	// check just in case the passed
	// IRQ doesn't match the limit
	if (irq > 15) // doesn't require a below zero check
		return;

	// declare required variables
	uint16_t pic_port; // port of the PIC
	uint8_t irq_mask;  // mask controlling which IRQ
					   // is enabled/disabled

	// check whether the IRQ is in the master
	// PIC or the slave PIC
	if (irq < 8)
		//
		pic_port = MASTER_PIC_DATA_PORT;
	else
	{
		pic_port = SLAVE_PIC_DATA_PORT;
		irq -= 8;
	}

	// get the IRQ mask byte
	irq_mask = inb(pic_port);
	// set the IRQ mask (to disable it)
	irq_mask |= (1 << irq);

	// write the IRQ mask to
	// the PIC port
	outb(pic_port, irq_mask);
}

void pic_disable_all_irqs(void)
{
	// iterates through each IRQ and
	// disables it
	for (uint8_t i = 0; i < 16; i++)
		pic_disable_irq(i);
}

void pic_send_eoi(uint8_t irq)
{
	outb(MASTER_PIC_COMMAND_PORT, 0x20);
	if (irq >= 8)
		outb(SLAVE_PIC_COMMAND_PORT, 0x20);
}
