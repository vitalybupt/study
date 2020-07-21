#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int64_t IntegerMul_(int8_t a, int16_t b, int32_t c, int64_t d, int8_t e, int16_t f, int32_t g, int64_t h);

static void print_(const char** s) {
  int len = strlen(s[1]);
  printf("%d, %s\r\n", len, s[1]);
  return;
}

void main() {
  const char* src[] = {"One", "Tow", "Three", "Four"};
  printf("%d\r\n", IntegerMul_(1, 2, 3, 4, 5, 6, 7, 8));
  print_(src);
  return;
}
