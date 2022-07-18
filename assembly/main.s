	.file	"main.cpp"
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
	.align 8
.LC0:
	.string	"raylib [core] example - basic window"
	.align 8
.LC1:
	.string	"Congrats! You created your first window!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1761:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$23, %edi
	call	_Z3fooi
	movl	$9, -20(%rbp)
	movl	$.LC0, %edx
	movl	$450, %esi
	movl	$800, %edi
	call	InitWindow
	jmp	.L2
.L3:
	call	BeginDrawing
	movl	-40(%rbp), %ecx
	movb	$-11, %cl
	movl	$-11, %eax
	movb	%al, %ch
	andl	$-16711681, %ecx
	movl	%ecx, %eax
	orl	$16056320, %eax
	orl	$-16777216, %eax
	movl	%eax, -40(%rbp)
	movl	%eax, %edi
	call	ClearBackground
	movb	$-56, %bl
	movl	$-56, %eax
	movb	%al, %bh
	movl	%ebx, %eax
	andl	$-16711681, %eax
	orl	$13107200, %eax
	movl	%eax, %ebx
	movl	%ebx, %eax
	orl	$-16777216, %eax
	movl	%eax, %ebx
	movl	%ebx, %r8d
	movl	$20, %ecx
	movl	$200, %edx
	movl	$190, %esi
	movl	$.LC1, %edi
	call	DrawText
	call	EndDrawing
.L2:
	call	WindowShouldClose
	xorl	$1, %eax
	testb	%al, %al
	jne	.L3
	call	CloseWindow
	movl	$0, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1761:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2285:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L7
	cmpl	$65535, -8(%rbp)
	jne	.L7
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L7:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2285:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2286:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2286:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 12.1.1 20220507 (Red Hat 12.1.1-1)"
	.section	.note.GNU-stack,"",@progbits
