.section ".text.boot"

.global _start

// entry point
_start:
	mov sp, #0x8000

	// clear .bss
	ldr		r3, =__bss_end__
	ldr		r2, =__bss_start__
	cmp		r2, r3
	bcs		2f
	sub		r3, r2, #1
	ldr		r1, =__bss_end__
	sub		r1, r1, #1
	mov		r2, #0
1:	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	1b

	// main
2:	bl kernel_main

hang: b hang
