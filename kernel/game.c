#include <game.h>
#include <stdint.h>
#include <vga.h>

int i = 0;

void setup() {
	vga_setp(0, 0, 0xF);
}

void tick() {
	
}

void update() {
	vga_setp(0, 0, (vga_getp(0, 0) ? 0x0 : 0xF));
	i++;
}
