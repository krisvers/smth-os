#include <stdio.h>
#include <string.h>
#include <cpuid.h>
#include <vga.h>
#include <gfx/gfx.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <pic.h>
#include <pit.h>

struct gpRegs {
	uint32_t eax, ebx, ecx, edx;
};

void pix(Registers * regs) {
	vga_setp(0, 0, 0x0F);
}

void unpix(Registers * regs) {
	vga_setp(0, 0, 0x00);
}

void main() {
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
	pit_init();

//	vga_pallete_test();

//	pit_register_event(pix, 1000, 0);
//	pit_register_event(unpix, 1000, 1000);
}
