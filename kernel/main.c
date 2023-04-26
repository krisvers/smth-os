#include <game.h>
#include <stdio.h>
#include <string.h>
#include <cpu.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <pic.h>
#include <pit.h>

void update_event(Registers * regs) {
	update();
}

void tick_event(Registers * regs) {
	tick();
}

void main() {
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
	pit_init();
	cpu_features();

	setup();

	pit_register_event(update_event, 16, 0);
	pit_register_event(tick_event, 7, 0);
}
