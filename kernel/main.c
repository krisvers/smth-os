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

	for (int a = 0; a < 640; a++) {
		for (int b = 0; b < 200; b++) {
			vga_setp(a, b, 1);
		}
	}

	puts("hello\tworld\nnewline\ntest\bs");
}
