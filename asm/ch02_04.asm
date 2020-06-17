	/*			
	 int32_t IntegerMulDiv_(int32_t a, int32_t b, int32_t *prod);
	 return: 0 = error (b equals 0), 1 = success
	*/
	
	.file "ch02_04.asm"
	.text
	.type IntegerMulDiv_, @function
	.globl IntegerMulDiv_
IntegerMulDiv_:
	movl %esi, %eax
	or %eax, %eax
	jz InvalidDivisor
	movl $1, %eax
InvalidDivisor:
	ret
	
	
