	.file "ch02_01.asm"
	.text
	.globl IntegerAddSub_
	.type IntegerAddSub_, @function
IntegerAddSub_:	
	movl %edi, %eax
	addl %esi, %eax
	subl %edx, %eax
	ret
	
