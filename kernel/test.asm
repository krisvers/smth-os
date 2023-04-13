[bits 32]

section ".text"

extern putc

global test
test:
	push ebp
	mov ebp, esp

	mov eax, [esp + 8]
	
	push byte eax
	call putc
	
	add esp, 4

	pop ebp

	ret

section ".data"

CURSOR dd 0xB8000
