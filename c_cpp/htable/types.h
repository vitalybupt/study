#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H
#include <stdint.h>

typedef uint64_t u64;
typedef int64_t s64;

typedef uint32_t u32;
typedef int32_t s32;

typedef uint16_t u16;
typedef int16_t s16;

typedef uint8_t  u8;
typedef int8_t  s8;

#ifndef __WORDSIZE
#define __WORDSIZE (__SIZEOF_LONG__ * 8)
#endif

#ifndef BITS_PER_LONG
#define BITS_PER_LONG __WORDSIZE
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr)[0])
#endif
