	.file	"1-main.c"
	.text
	.section	.rodata
.LC0:
	.string	"Holberton School"
.LC1:
	.string	"1-main.c"
	.align 8
.LC2:
	.string	"strcmp(S1, S1) == asm_strcmp(S1, S1)"
.LC3:
	.string	""
	.align 8
.LC4:
	.string	"strcmp(S1, S2) == asm_strcmp(S1, S2)"
.LC5:
	.string	"Holberton Socool"
	.align 8
.LC6:
	.string	"strcmp(S1, S3) == asm_strcmp(S1, S3)"
.LC7:
	.string	"All good!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	asm_strcmp@PLT
	testl	%eax, %eax
	je	.L2
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$22, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L2:
	leaq	.LC3(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	asm_strcmp@PLT
	cmpl	$1, %eax
	je	.L3
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$23, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L3:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	asm_strcmp@PLT
	cmpl	$-1, %eax
	je	.L4
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$24, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L4:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 5
__PRETTY_FUNCTION__.0:
	.string	"main"
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
