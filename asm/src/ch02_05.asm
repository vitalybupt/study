	.file "ch02_05.asm"
	.text
	.globl IntegerMul_
	.type IntegerMul_, @function
	/*
	int64_t IntegerMul_(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h)
	call convention for unix: rdi, rsi, rdx, rcx, r8, r9
	call convention for VS: rcx, rdx, r8, r9
	callee register: rdi, rsi, rdx, rcx, r8, r9, r10, r11
	caller register: rbx, rbp, r12 - r15
	*/
IntegerMul_:
	movsx %dil, %rax /* sign extend a from 8bit to 64bit and saved to  rax */
	movsx %si, %rsi /* sign extend b from 16bit to 64bit */
	imul %rsi, %rax   /* rax = a*b  */
	movsxd %edx, %rdx /* sign extend c from 32bit to 64bit */
	imul %rcx, %rdx /* c = c*d */
	imul %rdx, %rax /* rax = a*b*c*d */
	movsx %r8b, %r8 /* sign extend e from 8 bit to 64bit */
	movsx %r9w, %r9
	imul %r9, %r8 /* r8 = e*f */
	imul %r8, %rax /* rax = a*b*c*d*e*f */
	movsxd 16(%rsp), %rcx
	movq  8(%rsp), %rdx
	imul %rcx, %rdx
	imul %rdx, %rax
	ret
