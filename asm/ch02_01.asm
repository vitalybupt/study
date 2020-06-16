	.file "ch02_01.c"
	.text
	.type IntegerAddSub_, @function
IntegerAddSub_:	
	movl %eax, %ecx
	addl %eax, %edx
	subl %eax, %r9d
	ret
	
