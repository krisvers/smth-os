bits 32

extern _BSS_START
extern _BSS_END

section ".entry"

global _kentry
_kentry:
	mov eax, _BSS_START

	.bss:
		mov byte [eax], 0

		inc eax
		cmp eax, _BSS_END
		jne .bss

	mov word [0xB8000], 0x024B

	jmp $
