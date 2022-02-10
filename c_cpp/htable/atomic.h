/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_COMPILER_H_
#define _LINUX_COMPILER_H_

#include <types.h>

/* Optimization barrier */
/* The "volatile" is due to gcc bugs */
#define barrier() __asm__ __volatile__("": : :"memory")

/*
 * Following functions are taken from kernel sources and
 * break aliasing rules in their original form.
 *
 * While kernel is compiled with -fno-strict-aliasing,
 * perf uses -Wstrict-aliasing=3 which makes build fail
 * under gcc 4.4.
 *
 * Using extra __may_alias__ type to allow aliasing
 * in this case.
 */
typedef u8  __attribute__((__may_alias__))  u8_alias_t;
typedef u16 __attribute__((__may_alias__)) u16_alias_t;
typedef u32 __attribute__((__may_alias__)) u32_alias_t;
typedef u64 __attribute__((__may_alias__)) u64_alias_t;

static __always_inline void __read_once_size(const volatile void *p, void *res, int size)
{
	switch (size) {
	case 1: *(u8_alias_t  *) res = *(volatile u8_alias_t  *) p; break;
	case 2: *(u16_alias_t *) res = *(volatile u16_alias_t *) p; break;
	case 4: *(u32_alias_t *) res = *(volatile u32_alias_t *) p; break;
	case 8: *(u64_alias_t *) res = *(volatile u64_alias_t *) p; break;
	default:
		barrier();
		__builtin_memcpy((void *)res, (const void *)p, size);
		barrier();
	}
}

static __always_inline void __write_once_size(volatile void *p, void *res, int size)
{
	switch (size) {
	case 1: *(volatile  u8_alias_t *) p = *(u8_alias_t  *) res; break;
	case 2: *(volatile u16_alias_t *) p = *(u16_alias_t *) res; break;
	case 4: *(volatile u32_alias_t *) p = *(u32_alias_t *) res; break;
	case 8: *(volatile u64_alias_t *) p = *(u64_alias_t *) res; break;
	default:
		barrier();
		__builtin_memcpy((void *)p, (const void *)res, size);
		barrier();
	}
}

/*
 * Prevent the compiler from merging or refetching reads or writes. The
 * compiler is also forbidden from reordering successive instances of
 * READ_ONCE and WRITE_ONCE, but only when the compiler is aware of some
 * particular ordering. One way to make the compiler aware of ordering is to
 * put the two invocations of READ_ONCE or WRITE_ONCE in different C
 * statements.
 *
 * These two macros will also work on aggregate data types like structs or
 * unions. If the size of the accessed data type exceeds the word size of
 * the machine (e.g., 32 bits or 64 bits) READ_ONCE() and WRITE_ONCE() will
 * fall back to memcpy and print a compile-time warning.
 *
 * Their two major use cases are: (1) Mediating communication between
 * process-level code and irq/NMI handlers, all running on the same CPU,
 * and (2) Ensuring that the compiler does not fold, spindle, or otherwise
 * mutilate accesses that either do not require ordering or that interact
 * with an explicit memory barrier or atomic instruction that provides the
 * required ordering.
 */

#define READ_ONCE(x)					\
({							\
	union { typeof(x) __val; char __c[1]; } __u =	\
		{ .__c = { 0 } };			\
	__read_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__val;					\
})

#define WRITE_ONCE(x, val)				\
({							\
	union { typeof(x) __val; char __c[1]; } __u =	\
		{ .__val = (val) }; 			\
	__write_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__val;					\
})


#ifndef __fallthrough
# define __fallthrough
#endif

#endif /* _TOOLS_LINUX_COMPILER_H */
