ENTRY(_start)

SECTIONS
{
	. = 0x7c00;

	/* bootloader */
	.bootloader :
	{
		*(.bootloader)
	}

	. = 0x1000;

	/* multiboot header */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* readonly data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* uninitialized read write */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

}
