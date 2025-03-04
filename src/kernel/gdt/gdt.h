#include <stdint.h>

#ifndef GDT_H
#define GDT_H

struct gdt_entry
{
	uint32_t base;		 // gdt gate address
	uint32_t limit : 20; // segment limit
	uint8_t access;
	uint8_t flags;
} __attribute__((packed));

struct gdt_pointer
{
	uint32_t base;
	uint16_t limit;

} __attribute__((packed));

extern struct gdt_entry gdt_entries[3];

extern struct gdt_pointer gdt_pointer;

#endif

void gdt_setup_entry(
	int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_setup(void);
