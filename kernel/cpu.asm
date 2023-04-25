bits 32

global cli
cli:
	cli

	ret

global sti
sti:
	sti

	ret

global hlt
hlt:
	hlt

	ret

; struct gpRegs cpuid(eax, ebx, ecx, edx);
global cpuid
cpuid:
	push ebp

	mov ebp, esp
	
	mov eax, [esp + 20]
	mov ebx, [esp + 16]
	mov ecx, [esp + 12]
	mov edx, [esp + 8]

	cpuid

	pop ebp

	ret
