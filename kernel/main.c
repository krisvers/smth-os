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

	vga_pallete_test();

	puts("hello\tworld\nnewline\ntest\bs");
}
