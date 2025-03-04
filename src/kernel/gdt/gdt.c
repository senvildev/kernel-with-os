#include <stdint.h>

#include "gdt.h"

struct gdt_entry gdt_entries[3];

struct gdt_pointer gdt_pointer;

void gdt_entry_setup(
	int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	struct gdt_entry gdt_entry_target = gdt_entries[num];

	gdt_entry_target.base = base;
	gdt_entry_target.limit = limit & 0xFFFFF;
	gdt_entry_target.access = access;
	gdt_entry_target.flags = flags | ((limit >> 16) & 0xF);
}

void gdt_setup(void)
{
	gdt_pointer.limit = sizeof(gdt_entries) - 1;
	gdt_pointer.base = (uint32_t)(uintptr_t)&gdt_entries;

	gdt_entry_setup(0, 0, 0, 0, 0);

	gdt_entry_setup(1, 0x00, 0xFFFFF, 0x9A, 0xCF);
	gdt_entry_setup(2, 0x00, 0xFFFFF, 0x92, 0xCF);

	asm volatile("lgdt (%0) " : : "r"(&gdt_pointer));
}
