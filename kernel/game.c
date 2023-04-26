#include <game.h>
#include <stdint.h>
#include <vga.h>
#include <font.h>

int i = 0;

void setup() {
	vga_setp(i, 0, 0xF);
}

void tick() {
	i++;
}

void update() {
	font_putc(i * 8, 0, i, 0xF);

	vga_swap_buffer();
	//vga_clear();
}
