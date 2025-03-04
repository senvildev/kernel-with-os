#include <stdint.h>

#include "gdt.h"

// create gdt entry table
struct gdt_entry gdt_entries[GDT_TABLE_SIZE];

struct gdt_pointer gdt_pointer;

void gdt_entry_setup(
	int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	// get the segment element from the GDT
	struct gdt_entry *gdt_entry_target = &gdt_entries[num];

	// limit low - mask lower 16 bits (20-bit limit)
	gdt_entry_target->limit_low = limit & 0xFFFFF;
	// upper 4 bits of the limit
	gdt_entry_target->limit_high = (limit >> 16) & 0x0F;
	// granularity of the segment based on the flags
	gdt_entry_target->limit_high |= (flags & 0x0F);

	// lower 16 bits of the start address
	gdt_entry_target->base_low = base & 0xFFFFF;
	// set next 8 bits of the address
	gdt_entry_target->base_mid = (base >> 16) & 0xFF;
	// upper 8 bits of the address
	gdt_entry_target->base_high = (base >> 24) & 0xFF;

	// access byte - pretty straightforward
	gdt_entry_target->access = access;
}

void gdt_setup(void)
{
	// get the size of the GDT
	gdt_pointer.limit = sizeof(gdt_entries) - 1;
	// get the address of the GDT
	gdt_pointer.base = (uint32_t)(uintptr_t)&gdt_entries;

	// create a null descriptor
	gdt_entry_setup(0, 0, 0, 0, 0);
	// create a kernel mode code segment
	gdt_entry_setup(1, 0x00400000, 0x003FFFFF, 0x9A, 0xC);
	// create a kernel mode data segment
	gdt_entry_setup(2, 0x00800000, 0x003FFFFFF, 0x92, 0xC);

	// load the gdt using assembly
	asm volatile("lgdt (%0) " : : "r"(&gdt_pointer));
}
