#include <game.h>
#include <stdint.h>
#include <stdio.h>
#include <vga.h>
#include <font.h>

int i = 0;

void setup() {
	vga_pallete_test();
}

void tick() {
}

void update() {
	printf("amoogus\nin real life\n%x%b\n", 0x69420, 0b001011011);
	vga_swap_buffer();
	//vga_clear();
}
