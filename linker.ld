ENTRY(_start)
SECTIONS
{
	. = 0x8000;
	.text : {
		KEEP(*(.text.boot))
		*(.text)
	}
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	__bss_start__ = .;
	.bss : { *(.bss) }
	__bss_end__ = .;
}
