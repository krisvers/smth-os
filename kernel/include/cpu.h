#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
	uint32_t ds;
	uint32_t edi, esi, ebp, kern_esp, ebx, ecx, edx, eax;
	uint32_t interrupt, error;
	uint32_t eip, cs, cflags, esp, ss;
} __attribute__((packed)) Registers;

struct cpuFeatures {
	uint32_t version, additional, features_a, features_b;
};

void cli();
void sti();
void hlt();

void cpu_features();
char * cpu_get_model();
void cpuid(uint32_t value, uint32_t * eax, uint32_t * ebx, uint32_t * ecx, uint32_t * edx);

#endif
