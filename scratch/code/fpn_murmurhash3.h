/*
 * Copyright 2014 6WIND, All rights reserved.
 */

/* MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain. The author hereby disclaims copyright to this source code. */

/*
 * From https://code.google.com/p/smhasher we have on a Core i5 @ 3ghz:
 *
 * fpn_murmurhash3     - ~3 gigs/second, ~29 cycles per a 16-byte key
 * fpn_murmurhash3_128 - ~7.5 gigs/second, ~30 cycles per 16-byte key
 * lookup3 (jhash) for comparison - ~1.5 gigs/second, ~42 cycles per 16-byte key
 *
 * So:
 * - for hashing keys larger than 16 bytes, fpn_murmurhash3_128() should
 *   be faster
 * - for smaller keys, except is more than 32-bits hash is required,
 *   fpn_murmurhash3() version is enough
 * - in any case, murmurhash looks faster than jhash
 */

#ifndef __FPN_MURMURHASH_H__
#define __FPN_MURMURHASH_H__

#include <stdint.h>

/* 32-bit rotation */
static inline uint32_t fpn_murmurhash_rotl32(uint32_t x, int8_t r)
{
	return (x << r) | (x >> (32 - r));
}

/* add 32-bit to the 32-bit hash */
__attribute__((always_inline))
static inline uint32_t fpn_murmurhash3_add32(uint32_t h, uint32_t data)
{
	data *= 0xcc9e2d51;
	data = fpn_murmurhash_rotl32(data, 15);
	data *= 0x1b873593;
	h ^= data;
	return h;
}

/* Intermediate mix for 32-bit hash */
__attribute__((always_inline))
static inline uint32_t fpn_murmurhash3_mix32(uint32_t h)
{
	h = fpn_murmurhash_rotl32(h,13);
	h = h * 5 +0xe6546b64;
	return h;
}

/* Finalization mix for 32-bit hash - force all bits of a hash block to
 * avalanche */
static inline uint32_t fpn_murmurhash3_fmix32(uint32_t h)
{
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;

	return h;
}

/* 64-bit rotation */
static inline uint64_t fpn_murmurhash_rotl64(uint64_t x, int8_t r)
{
	return (x << r) | (x >> (64 - r));
}

/* add first 64-bit to the 128-bit hash */
static inline uint64_t fpn_murmurhash3_add64_1(uint64_t h, uint64_t data)
{
	data *= 0x87c37b91114253d5ULL;
	data  = fpn_murmurhash_rotl64(data, 31);
	data *= 0x4cf5ad432745937fULL;
	h ^= data;
	return h;
}

/* add second 64-bit to the 128-bit hash */
static inline uint64_t fpn_murmurhash3_add64_2(uint64_t h, uint64_t data)
{
	data *= 0x4cf5ad432745937fULL;
	data  = fpn_murmurhash_rotl64(data, 33);
	data *= 0x87c37b91114253d5ULL;
	h ^= data;
	return h;
}

/* Intermediate 64-bit mix for 128-bit hash */
static inline uint64_t fpn_murmurhash3_mix64_1(uint64_t h1, uint64_t h2)
{
	h1 = fpn_murmurhash_rotl64(h1,27);
	h1 += h2;
	h1 = h1 * 5 + 0x52dce729ULL;
	return h1;
}

/* Intermediate first 64-bit mix for 128-bit hash */
static inline uint64_t fpn_murmurhash3_mix64_2(uint64_t h1, uint64_t h2)
{
	h2 = fpn_murmurhash_rotl64(h2,31);
	h2 += h1;
	h2 = h2 * 5 + 0x38495ab5ULL;
	return h2;
}

/* Finalization 64-bit mix for 128-bit hash - force all bits of a hash
 * block to avalanche */
static inline uint64_t fpn_murmurhash3_fmix64(uint64_t k)
{
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccdULL;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53ULL;
	k ^= k >> 33;
	return k;
}

/*
 * MurmurHash3 32-bit
 *
 * "MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain. The author hereby disclaims copyright to this source code."
 *
 * References:
 *     https://code.google.com/p/smhasher/
 *
 * param key
 *   the key (the unaligned variable-length array of bytes)
 * param len
 *   the length of the key, counting by bytes
 * param seed
 *   can be any 4-byte value initialization value
 * return
 *   a 32-bit hash
 */
static inline uint32_t fpn_murmurhash3(const void *key, int len, uint32_t seed)
{
	const uint8_t *data = (const uint8_t *)key;
	const uint8_t *tail;
	const int nblocks = len / 4;
	uint32_t h1 = seed;
	uint32_t k1;
	const uint32_t *blocks = (const uint32_t *)(data + nblocks * 4);
	int i;

	/* body */
	for (i = -nblocks; i; i++) {
		k1 = blocks[i];
		h1 = fpn_murmurhash3_add32(h1, k1);
		h1 = fpn_murmurhash3_mix32(h1);
	}

	/* tail */
	tail = (const uint8_t *)(data + nblocks * 4);
	k1 = 0;

	switch(len & 3) {
	case 3: k1 ^= tail[2] << 16; /* fall through */
	case 2: k1 ^= tail[1] << 8; /* fall through */
	case 1: k1 ^= tail[0]; /* fall through */
		h1 = fpn_murmurhash3_add32(h1, k1);
	};

	/* finalization */
	h1 ^= len;
	h1 = fpn_murmurhash3_fmix32(h1);
	return h1;
}

/*
 * MurmurHash3 128-bit (uses 64-bit variables)
 *
 * "MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain. The author hereby disclaims copyright to this source code."
 *
 * References:
 *     https://code.google.com/p/smhasher/
 *
 * param key
 *   the key (the unaligned variable-length array of bytes)
 * param len
 *   the length of the key, counting by bytes
 * param seed
 *   can be any 4-byte value initialization value
 * param out
 *   a pointer to a 128-bit (16 bytes) memory zone where the hash will
 *   be written
 */
//void fpn_murmurhash3_128(const void *key, int len, uint32_t seed, void *out);

#endif /* __FPN_MURMURHASH_H__ */
