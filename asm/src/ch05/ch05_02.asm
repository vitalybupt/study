	.file "ch05_02.asm"
	.text
	.global calc_sphere_area_volume
	.type calc_sphere_area_volume, @function
calc_sphere_area_volume:
	vmovsd (.LC1), %xmm0
	ret
	.size	calc_sphere_area_volume, .-calc_sphere_area_volume
	.align 8
.LC1:
	.double 0e1.25, 0e3
	
	
	
