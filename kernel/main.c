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

struct pageDesc {
	void * start;
	uint16_t first_free;
	uint16_t free_contiguous;
	uint16_t length;
} __attribute__ ((packed));

void * pages_start = (void *) 0x100000;
void * pages_end = (void *) 0xEFFFFF;
uint16_t page_size = 4096;

uint16_t pages_num = 0;
struct pageDesc pages[256];

struct pageDesc * page_new(void * ptr, uint8_t size) {
	pages[pages_num] = (struct pageDesc) {
		.start = ptr,
		.first_free = 0,
		.free_contiguous = size * page_size,
		.length = size * page_size,
	};

	return &pages[pages_num++];
}

void page_print(struct pageDesc * p) {
	printf("%x: addr: %x, ");
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
