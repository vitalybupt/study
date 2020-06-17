#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

extern int32_t IntegerMulDiv_(int32_t a, int32_t b, int32_t *prod);

void main() {
  int32_t prod;
  assert(IntegerMulDiv_(2,0,&prod) == 0);
  return;
}
