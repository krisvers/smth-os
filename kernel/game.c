#include <game.h>
#include <stdint.h>
#include <stdio.h>
#include <vga.h>
#include <font.h>

void setup() {
	vga_pallete_test();
	printf("sussy baka\n");
}

void tick() {

}

void update() {
	vga_swap_buffer();
	//vga_clear();
}
