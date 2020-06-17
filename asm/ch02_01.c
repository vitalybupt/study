#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern int32_t IntegerAddSub_(int32_t a, int32_t b, int32_t c);

void main() {
  printf("%d\r\n", IntegerAddSub_(6, 6, 7));
  return;
}
