#include <stdlib.h>
#include <stdio.h>
#include <cpu.h>
#include <vga.h>

void abort() {
	printf("Kernel panic!\n");
	vga_pallete_test();
	vga_set_background(0x28);
	vga_swap_buffer();

	cli();
	hlt();

	for (;;);

	__builtin_unreachable();
}
