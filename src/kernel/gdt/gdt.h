#include <stdint.h>

// GDT segment entry structure
struct gdt_entry
{
	uint16_t limit_low;	   // low 16 bits of the limit
	uint16_t base_low;	   // lower 16 bits of the start address
	uint8_t base_mid;	   // middle 8 bits of the start address
	uint8_t access;		   // access byte
	uint8_t limit_high;	   // upper 8 limits of the limit
	uint8_t base_high;	   // upper 8 bits of the start address
} __attribute__((packed)); // disable margins between variables

// GDT info structure containing:
//	  - limit - size of the GDT
//	  - base - location address of the GDT
struct gdt_pointer
{
	uint16_t limit;		   // location of the GDT
	uint32_t base;		   // address of the GDT
} __attribute__((packed)); // disable margins between variables

#ifndef GDT_H
#define GDT_H

#define GDT_TABLE_SIZE 3

// GDT table
extern struct gdt_entry gdt_entries[GDT_TABLE_SIZE];

// pointer to the GDT
extern struct gdt_pointer gdt_pointer;

#endif

// sets up an entry
// arguments:
//	  - num - which gate in the table to change
//	  - base - starting address of the entry
//	  - limit - size of the segment (how far it extends from the base)
//	  - access - defines access rights to the entry
//	  - flags - the granularity of the entry
void gdt_setup_entry(
	int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

// sets up all gates required by the system
void gdt_setup(void);
