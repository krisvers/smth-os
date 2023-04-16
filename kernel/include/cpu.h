#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
	uint32_t ds;
	uint32_t edi, esi, ebp, kern_esp, ebx, ecx, edx, eax;
	uint32_t interrupt, error;
	uint32_t eip, cs, cflags, esp, ss;
} __attribute__((packed)) Registers;

void cli();
void sti();
void hlt();

#endif
