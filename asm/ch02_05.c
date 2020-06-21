#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int64_t IntegerMul_(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h);

void main() {
  printf("%d\r\n", IntegerMul_(1, 2, 3, 4, 5, 6, 7, 8));
  return;
}
