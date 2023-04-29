#include <game.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
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

struct freeDesc {
	void * ptr;
	size_t size;
};

struct pageDesc {
	void * start;
	uint16_t length;
	struct freeDesc free[256];
} __attribute__ ((packed));

void * pages_start = (void *) 0x100000;
void * pages_end = (void *) 0xEFFFFF;
uint16_t page_size = 4096;

uint16_t pages_num = 0;
struct pageDesc pages[256];

struct pageDesc * page_new(void * ptr, uint8_t size) {
	pages[pages_num] = (struct pageDesc) {
		.start = ptr,
		.length = size * page_size,
	};

	pages[pages_num].free[0].ptr = pages[pages_num].start;
	pages[pages_num].free[0].size = pages[pages_num].length;

	return &pages[pages_num++];
}

void * malloc(size_t size) {
	if (size == 0) {
		return NULL;
	}

	for (size_t i = 0; 1; i++) {
		if (i >= pages_num) {
			printf("ran out of physical memory!\n");

			return NULL;
		}

		struct pageDesc page = pages[i];
		void * ptr;

		size_t j;
		for (j = 0; ; j++) {
			if (page.free[j].size < size || page.free[j].ptr == NULL || page.free[j].size == 0) {
				goto next_page;
			}

			if (page.free[j].size > size) {
				goto found_free;
			}
		}

found_free:
		printf("found free %x %d  ", page.free[j].ptr, page.free[j].size);

		ptr = page.free[j].ptr;

		page.free[j].size -= size;
		page.free[j].ptr += size;

		printf("%x %d\n", page.free[j].ptr, page.free[j].size);

		if (page.free[j].size > page_size || page.free[j].size == 0) {
			page.free[j].size = 0;
			page.free[j].ptr = NULL;
		}

		for (size_t k = 0; page.free[j].size < page.free[k].size; k++) {
			struct freeDesc tmp = page.free[j];

			page.free[j++] = page.free[k];
			page.free[k] = tmp;

			printf("swap\n");
		}

		return ptr;

next_page:
	}
}

void free(void * ptr, size_t size) {
}

void page_print(struct pageDesc * p) {
	printf("%x: addr: %x, page length %d\n", p, p->start, p->length);
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

	page_print(page_new(pages_start, 1));

	while (malloc(1));
}
