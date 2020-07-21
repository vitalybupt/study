	.file "ch03_07.asm"
	.text
	.global ConcatStrings_
	.type ConcatStrings_, @function
	/*
	size_t ConcatStrings_(char* des, size_t des_size, const char* const* src, size_t src_n) ;
	call convention: rdi, rsi, rdx, rcx, r8, r9
	call convention for VS: rcx, rdx, r8, r9	
	caller registers: rbx, rbp, r12 - r15
	callee registers: rdi, rsi, rdx, rcx, rax, r8, r9, r10, r11
	*/
ConcatStrings_:
	push %rbx
	/* set error code */
	mov $-1, %rax

	/* test des_size */
	test %rsi, %rsi
	jz InvalidArg

	/* test src_n */
	test %rcx, %rcx
	jz InvalidArg

	/*
	initialize registers used in loop
	%rdx = src	%r11 = src size
	%r9 = dest      %r10 = dest size  
	%rbx = des_index
	%r8 = i
	%rcx = str length
	%rdi %rsi used in string manipulation, point to string
	*/
	
	/* i = 0 */
	xor %r8, %r8
	/* des_index = 0 */
	xor %rbx, %rbx
	/* %r9 is dest, %rdi will be used in scasb */
	mov %rdi, %r9
	/* %r10 is dest size, %rsi used in movsb */
	mov %rsi, %r10
	/* %r11 is src size, %rcx used in scasb */
	mov %rcx, %r11
	
Loop1:
	/* load src[i] to rdi to compute the len */
	mov %rdx, %rax
	mov (%rax, %r8, 8), %rdi
	mov %rdi, %rsi
	
	/* compute length of src[i] */
	xor %eax, %eax
	mov $-1, %rcx
	repne scasb
	not %rcx
	dec %rcx

	/* compute des_index */
	mov %rbx, %rax
	add %rcx, %rax
	/* compare with dest_size */
	cmp %r10, %rax
	jge Done


	/* copy src[i] to des[des_index] */
	inc %rcx
	lea (%r9, %rax), %rdi
	rep movsb

	/* length < dest_size, %rbx=old_des_index, %rax=new_des_index */
	mov %rax, %rbx

	inc %r8
	cmp %r11, %r8
	jl Loop1
	
Done:
	mov %rbx, %rax
InvalidArg:
	pop %rbx
	ret
	

	
	
