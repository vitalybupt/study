	.file "ch02_01.asm"
	.text
	.globl IntegerAddSub_
	.type IntegerAddSub_, @function
	;; call convention for unix: rdi, rsi, rdx, rcx, r8, r9
	;; call convention for VS: rcx, rdx, r8, r9
	;; callee register: rdi, rsi, rdx, rcx, r8, r9, r10, r11
	;; caller register: rbx, rbp, r12 - r15
IntegerAddSub_:	
	movl %edi, %eax
	addl %esi, %eax
	subl %edx, %eax
	ret
	
