[bits 32]

section ".text"

extern putc
extern puts

global test
test:
	push 'T'
	call putc
	add esp, 4

	push TEST_MSG
	call puts
	add esp, 4

	xor eax, eax

	ret

section ".data"

CURSOR dd 0xB8000
TEST_MSG db "EST", 0x0A, 0
