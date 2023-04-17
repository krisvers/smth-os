#ifndef GFX_H
#define GFX_H

#include <stdint.h>

struct gfxPrimitive {
	uint16_t w, h;
	int16_t x, y;
};

enum gfx_color {
	TEST = 0xF,
};

void gfx_draw_primitive_outline(struct gfxPrimitive * prim, uint16_t thickness, enum gfx_color color);

#endif
