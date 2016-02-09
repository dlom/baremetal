ENTRY(_start)
SECTIONS
{
	. = 0x10000;
	__start = .;
	.boot . : { boot.o(.text) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	.bss : { *(.bss) }
	__end = .;
}
