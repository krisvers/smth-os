	.file	"kentry.c"
	.text
	.section	.entry,"ax",@progbits
	.p2align 2
	.globl	_kentry
	.type	_kentry, @function
_kentry:
.LFB0:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	pushl	%eax
	.cfi_def_cfa_offset 16
	movl	$_BSS_START, %eax
	cmpl	$_BSS_END, %eax
	jnb	.L2
	movl	$_BSS_END, %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	negl	%eax
	movl	%eax, %ebx
	andl	$3, %ebx
	subl	$_BSS_START+1, %edx
	cmpl	$7, %edx
	jbe	.L9
	testl	%ebx, %ebx
	je	.L10
	movb	$0, _BSS_START
	testb	$2, %al
	je	.L11
	movb	$0, _BSS_START+1
	movl	$_BSS_START-1, %eax
	testb	$3, %al
	jne	.L12
	movb	$0, _BSS_START+2
	movl	$_BSS_START+3, %esi
.L4:
	subl	%ebx, %ecx
	leal	_BSS_START(%ebx), %eax
	movl	%ecx, %edx
	andl	$-4, %edx
	leal	_BSS_START(%ebx,%edx), %edx
	.p2align 2
.L6:
	movl	$0, (%eax)
	addl	$4, %eax
	cmpl	%edx, %eax
	jne	.L6
	movl	%ecx, %eax
	andl	$-4, %eax
	addl	%esi, %eax
	andl	$3, %ecx
	je	.L2
.L3:
	movb	$0, (%eax)
	leal	1(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 1(%eax)
	leal	2(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 2(%eax)
	leal	3(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 3(%eax)
	leal	4(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 4(%eax)
	leal	5(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 5(%eax)
	leal	6(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 6(%eax)
	leal	7(%eax), %edx
	cmpl	$_BSS_END, %edx
	jnb	.L2
	movb	$0, 7(%eax)
.L2:
	subl	$8, %esp
	.cfi_def_cfa_offset 24
	pushl	$6
	.cfi_def_cfa_offset 28
	pushl	$65
	.cfi_def_cfa_offset 32
	call	test
	addl	$512, %eax
	movw	%ax, 753664
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L8:
	jmp	.L8
.L11:
	movl	$_BSS_START+1, %esi
	jmp	.L4
.L10:
	movl	$_BSS_START, %esi
	jmp	.L4
.L12:
	movl	$_BSS_START+2, %esi
	jmp	.L4
.L9:
	movl	$_BSS_START, %eax
	jmp	.L3
	.cfi_endproc
.LFE0:
	.size	_kentry, .-_kentry
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
