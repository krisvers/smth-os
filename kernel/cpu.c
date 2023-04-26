#include <cpu.h>
#include <cpuid.h>

#define CPU_FEATA_FPU	(1 << 0)
#define CPU_FEATA_VME	(1 << 1)
#define CPU_FEATA_DE	(1 << 2)
#define CPU_FEATA_PSE	(1 << 3)
#define CPU_FEATA_TSC	(1 << 4)
#define CPU_FEATA_MSR	(1 << 5)
#define CPU_FEATA_PAE	(1 << 6)
#define CPU_FEATA_MCE	(1 << 7)
#define CPU_FEATA_CX8	(1 << 8)
#define CPU_FEATA_APIC	(1 << 9)
// reserved
#define CPU_FEATA_SEP	(1 << 11)
#define CPU_FEATA_MTRR	(1 << 12)
#define CPU_FEATA_PGE	(1 << 13)
#define CPU_FEATA_MCA	(1 << 14)
#define CPU_FEATA_CMOV	(1 << 15)
#define CPU_FEATA_PAT	(1 << 16)
#define CPU_FEATA_PSE36	(1 << 17)
#define CPU_FEATA_PSN	(1 << 18)
#define CPU_FEATA_CLFSH	(1 << 19)
// itanium ;-; #define CPU_FEAT_NX	(1 << 20)
#define CPU_FEATA_DS	(1 << 21)
#define CPU_FEATA_ACPI	(1 << 22)
#define CPU_FEATA_MMX	(1 << 23)
#define CPU_FEATA_FXSR	(1 << 24)
#define CPU_FEATA_SSE	(1 << 25)
#define CPU_FEATA_SSE2	(1 << 26)
#define CPU_FEATA_SS	(1 << 27)
#define CPU_FEATA_HTT	(1 << 28)
#define CPU_FEATA_TM	(1 << 29)
#define CPU_FEATA_IA64	(1 << 30)
#define CPU_FEATA_PBE	(1 << 31)

#define CPU_FEATB_SSE3		(1 << 0)
#define CPU_FEATB_PCLMULQDQ	(1 << 1)
#define CPU_FEATB_DTES64	(1 << 2)
#define CPU_FEATB_MONITOR	(1 << 3)
#define CPU_FEATB_DS_CPL	(1 << 4)
#define CPU_FEATB_VMX		(1 << 5)
#define CPU_FEATB_SMX		(1 << 6)
#define CPU_FEATB_EST		(1 << 7)
#define CPU_FEATB_TM2		(1 << 8)
#define CPU_FEATB_SSSE3		(1 << 9)
#define CPU_FEATB_CNXT_ID	(1 << 10)
#define CPU_FEATB_SDBG		(1 << 11)
#define CPU_FEATB_FMA		(1 << 12)
#define CPU_FEATB_CX16		(1 << 13)
#define CPU_FEATB_XTPR		(1 << 14)
#define CPU_FEATB_PDCM		(1 << 15)
// reserved
#define CPU_FEATB_PCID		(1 << 17)
#define CPU_FEATB_DCA		(1 << 18)
#define CPU_FEATB_SSE4_1	(1 << 19)
#define CPU_FEATB_SSE4_2	(1 << 20)
#define CPU_FEATB_X2APIC	(1 << 21)
#define CPU_FEATB_MOVBE		(1 << 22)
#define CPU_FEATB_POPCNT	(1 << 23)
#define CPU_FEATB_TSC_DEADLINE	(1 << 24)
#define CPU_FEATB_AES		(1 << 25)
#define CPU_FEATB_XSAVE		(1 << 26)
#define CPU_FEATB_OSXSAVE	(1 << 27)
#define CPU_FEATB_AVX		(1 << 28)
#define CPU_FEATB_F16C		(1 << 29)
#define CPU_FEATB_RDRND		(1 << 30)
#define CPU_FEATB_HYPERVISOR	(1 << 31)

static char cpu_model_str[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static uint32_t cpu_version_info;
static uint32_t cpu_additional_info;
static uint32_t cpu_feature_info_edx;
static uint32_t cpu_feature_info_ecx;

static inline uint8_t cpu_has_a(uint32_t i) {
	return cpu_feature_info_edx & i;
}

char * cpu_get_model() {
	if (cpu_model_str[0] == '\0') {
		uint32_t unused;
		cpuid(0, &unused, (uint32_t *) &cpu_model_str[0], (uint32_t *) &cpu_model_str[8], (uint32_t *) &cpu_model_str[4]);
	}

	return cpu_model_str;
}

struct cpuFeatures cpu_get_features() {
	if (!cpu_version_info) {
		cpu_features();
	}

	return (struct cpuFeatures) { cpu_version_info, cpu_additional_info, cpu_feature_info_edx, cpu_feature_info_ecx };
}

uint8_t cpu_has_fpu() {
	return cpu_has_a(CPU_FEATA_FPU);
}

uint8_t cpu_has_pae() {
	return cpu_has_a(CPU_FEATA_PAE);
}

uint8_t cpu_has_apic() {
	return cpu_has_a(CPU_FEATA_APIC);
}

void cpu_features() {
	cpuid(1, &cpu_version_info, &cpu_additional_info, &cpu_feature_info_ecx, &cpu_feature_info_edx);
}

void cpuid(uint32_t value, uint32_t * eax, uint32_t * ebx, uint32_t * ecx, uint32_t * edx) {
	__get_cpuid(value, eax, ebx, ecx, edx);
}
