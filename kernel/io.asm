bits 32

global inb
inb:
	push ebp
	mov ebp, esp

	mov dx, [esp + 8]

	xor eax, eax
	in al, dx

	pop ebp

	ret

global inw
inw:
	push ebp
	mov ebp, esp

	mov dx, [esp + 8]

	xor eax, eax
	in ax, dx

	pop ebp

	ret

global inl
inl:
	push ebp
	mov ebp, esp

	mov dx, [esp + 8]

	in eax, dx

	pop ebp

	ret

global outb
outb:
	push ebp
	mov ebp, esp

	mov dx, [esp + 8]
	mov eax, [esp + 12]

	out dx, al

	pop ebp

	ret

global outw
outw:
	push ebp
	mov ebp, esp

	mov dx, [esp + 8]
	mov eax, [esp + 12]

	out dx, ax

	pop ebp

	ret

global outl
outl:
	push ebp
	mov ebp, esp

	mov dx, [esp + 8]
	mov eax, [esp + 12]

	out dx, eax

	pop ebp

	ret
