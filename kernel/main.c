#include <game.h>
#include <stdio.h>
#include <string.h>
#include <cpu.h>
#include <vga.h>
#include <gfx/gfx.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <pic.h>
#include <pit.h>

void update_isr(Registers * regs) {
	update();
}

void tick_isr(Registers * regs) {
	tick();
}

void main() {
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
	pit_init();
	cpu_features();

	vga_pallete_test();

	setup();

	pit_register_event(update_isr, 16, 0);
	pit_register_event(tick_isr, 8, 0);
}
