#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <sys/stat.h>
#include <immintrin.h>
#include <fcntl.h>

#include "fpn_murmurhash3.h"
typedef struct vertex {
  char val[64*6];
} vertex_t;

uint64_t stride = 64*6*4;
uint64_t size = 128;

void hash_64byte(uint8_t data[64], uint8_t data2[64], uint8_t data3[64], uint8_t data4[64],uint32_t seed);

void prepare_data(vertex_t *array) {
  int randomData = open("/dev/urandom", O_RDONLY);
  if (randomData < 0)  {
    assert(0);
  }
  for(uint32_t i = 0; i < size; ++i) {
    vertex_t *p = array;
    ssize_t result = read(randomData, p, sizeof(vertex_t));
    if (result < 0) {
      assert(0);
    }
    ++array;
  }
}

void process_data(char *array) {
  uint32_t seed = 0xD201D5;
  register char *p;
  char *next;
  p = array;
  uint32_t ret;
  uint32_t ret2;
  for (uint32_t i = 0; i < size*6*64; i += stride) {
    p = &array[i];
    __builtin_prefetch(p+64*6*4, 0, 0);
    ret = fpn_murmurhash3(p, 64, seed);
    assert(ret);
    
    __builtin_prefetch(p+64*6*4*2, 0, 0);
    ret = fpn_murmurhash3(p+64*6, 64, seed);
    (void)ret;
    __builtin_prefetch(p+64*6*4*3, 0, 0);
    fpn_murmurhash3(p+64*6*2, 64, seed);
    (void)ret;
    __builtin_prefetch(p+64*6*4*4, 0, 0);
    fpn_murmurhash3(p+6*6*3, 64, seed);
    (void)ret;

    hash_64byte(p, p+64, p+64*2, p+64*3, seed);

    if(i+stride >= size*6) {
      next = &array[0];
    }else {
      next = &array[i+stride];
    }
    p = next;
  }
}


void hash_64byte(uint8_t data[64*4],uint32_t seed) {
#define DATA_LEN  64
  const int nblocks = DATA_LEN / 4;
  uint32_t h1 = seed;
  uint32_t k1;
  const uint32_t *blocks = (const uint32_t *)(data + DATA_LEN); // point to end of data

  uint32_t h2 = seed;
  uint32_t k2;
  const uint32_t *blocks2 = (const uint32_t *)(data2 + DATA_LEN); // point to end of data
  
  uint32_t h3 = seed;
  uint32_t k3;
  const uint32_t *blocks3 = (const uint32_t *)(data3 + DATA_LEN); // point to end of data
  
  uint32_t h4 = seed;
  uint32_t k4;
  const uint32_t *blocks4 = (const uint32_t *)(data4 + DATA_LEN); // point to end of data
  __m128i a,b,c;
  for (int8_t i = -nblocks; i; i++) {
    a = _mm_loadu_si128((__m128i*)data);
      k1 = blocks[i];
      k1 *= 0xcc9e2d51;
      k2 = blocks2[i];
      k2 *= 0xcc9e2d51;
      k3 = blocks3[i];
      k3 *= 0xcc9e2d51;
      k4 = blocks4[i];
      k4 *= 0xcc9e2d51;
      k1 = (k1 << 15) | (k1 >> 17);
      k1 *= 0x1b873593;
      h1 ^= k1;
      h1 = (h1 << 13) | (h1 >> 19);
      h1 = h1*5 + 0xe6546b64;

      k2 = (k2 << 15) | (k2 >> 17);
      k2 *= 0x1b873593;
      h2 ^= k2;
      h2 = (h2 << 13) | (h2 >> 19);
      h2 = h2*5 + 0xe6546b64;

      k3 = (k3 << 15) | (k3 >> 17);
      k3 *= 0x1b873593;
      h3 ^= k3;
      h3 = (h3 << 13) | (h3 >> 19);
      h3 = h3*5 + 0xe6546b64;

      k4 = (k4 << 15) | (k4 >> 17);
      k4 *= 0x1b873593;
      h4 ^= k4;
      h4 = (h4 << 13) | (h4 >> 19);
      h4 = h4*5 + 0xe6546b64;
  }
  
    h1 ^= DATA_LEN;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;
    printf("%u %u %u %u\n", h1, h2, h3, h4);
    return;
}

#if 0
void process_data_simd(char *array) {
  uint32_t seed = 0xD201D5;
  register char *p;
  char *next;
  p = array;
  uint32_t ret;
  // assume that all data with same length
#define DATA_LEN = 64
  const int nblocks = DATA_LEN / 4;
  
  for (uint32_t i = 0; i < size*6*64; i += stride) {
    p = &array[i];
    uint32_t h1 = seed;
    uint32_t k1;
    const uint32_t *blocks = (const uint32_t *)(data + DATA_LEN);
    for (i = -nblocks; i; i++) {
      k1 = blocks[i];
      k1 *= 0xcc9e2d51;
      k1 = (k1 << 15) | (k1 >> 17);
      k1 *= 0x1b873593;
      h1 ^= k1;
      h1 = (h1 << 13) | (k1 >> 19);
      h1 = h1*5 + 0xe6546b64;
    }
    
    h1 ^= DATA_LEN;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    
    __builtin_prefetch(p+64*6*4, 0, 0);
    ret = fpn_murmurhash3(p, 64, seed);
    assert(ret);
    __builtin_prefetch(p+64*6*4*2, 0, 0);
    ret = fpn_murmurhash3(p+64*6, 64, seed);
    (void)ret;
    __builtin_prefetch(p+64*6*4*3, 0, 0);
    fpn_murmurhash3(p+64*6*2, 64, seed);
    (void)ret;
    __builtin_prefetch(p+64*6*4*4, 0, 0);
    fpn_murmurhash3(p+6*6*3, 64, seed);
    (void)ret;

    if(i+stride >= size*6) {
      next = &array[0];
    }else {
      next = &array[i+stride];
    }
    p = next;
  }
}
#endif

void clear_cl(vertex_t *array) {
  for(int i = 0; i < size; ++i) {
    _mm_clflush( &array[i] );
  }
}
void main() {
  vertex_t *vertex_array = malloc(sizeof(vertex_t)*size);

  prepare_data(vertex_array);
  for(uint32_t i = 0; i < 100000; ++i) {
    process_data(vertex_array->val);
    clear_cl(vertex_array);
  }
  return;
}
