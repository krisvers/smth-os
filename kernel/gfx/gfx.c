#include <gfx/gfx.h>
#include <vga.h>
#include <stdint.h>

void gfx_draw_primitive_outline(struct gfxPrimitive * prim, uint16_t thickness, enum gfx_color color) {
	for (uint16_t w = 0; w < prim->w; w++) {
		for (uint16_t t = 0; t < thickness; t++) {
			vga_setp(prim->x + w, prim->y + t, color);
			vga_setp(prim->x + w, prim->y + prim->h - t, color);
		}
	}

	for (uint16_t h = 0; h < prim->h; h++) {
		for (uint16_t t = 0; t < thickness; t++) {
			vga_setp(prim->x + t, prim->y + h, color);
			vga_setp(prim->x + prim->w - t, prim->y + h, color);
		}
	}
}
