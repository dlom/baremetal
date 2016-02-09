.global _start
_start:
	mov sp, #0x10000
	bl kernel_main

hang: b hang
