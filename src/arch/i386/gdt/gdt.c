#include <stdint.h>

#include "drivers/vga/vga_text/vga_text.h"

#include "gdt.h"

#include "global/defines.h"

// create the GDT
struct gdt_entry gdt_entries[GDT_SEGMENT_LIMIT];
// create a GDT pointer to load into memory
struct gdt_pointer gdt_pointer;

// function to setup singular entries in the GDT
void gdt_set_entry(
	int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	// stop code if the number is incorrect
	if (num < 0 || num >= GDT_SEGMENT_LIMIT)
	{
		vga_text_write_string(
			"error: couldn't add GDT segment - incorrect table size");
		return;
	}

	// get the segment element from the GDT
	struct gdt_entry *gdt_entry_target = &gdt_entries[num];

	// limit low - mask lower 16 bits (20-bit limit)
	gdt_entry_target->limit_low = limit & 0xFFFF;
	// upper 4 bits of the limit
	gdt_entry_target->limit_high = (limit >> 16) & 0x0F;
	// granularity of the segment based on the flags
	gdt_entry_target->limit_high |= (flags & 0xF0);

	// lower 16 bits of the start address
	gdt_entry_target->base_low = base & 0xFFFF;
	// set next 8 bits of the address
	gdt_entry_target->base_mid = (base >> 16) & 0xFF;
	// upper 8 bits of the address
	gdt_entry_target->base_high = (base >> 24) & 0xFF;

	// access byte - pretty straightforward
	gdt_entry_target->access = access;
}

// function to setup and load the GDT
void gdt_load(void)
{
	vga_text_write_string("info: loading the GDT");
	// get the size of the GDT
	gdt_pointer.limit = sizeof(gdt_entries) - 1;
	// get the address of the GDT
	gdt_pointer.base = (uint32_t)(uintptr_t)&gdt_entries;
	// load the gdt using assembly
	asm volatile("lgdt %0" : : "m"(gdt_pointer));

	vga_text_write_string("success: loaded the GDT");
}
