#include <stdio.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <pic.h>
#include <pit.h>

void main() {
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
	pit_init();

	for (int a = 0; a < 1600; a++) {
		for (int b = 0; b < 1200; b++) {
			vga_setp(a, b, a);
		}
	}

	puts("hello\tworld\nnewline\ntest\bs");
}
