#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"
int main() {
  int i = 3;
  assert(ALIGN(3,4) == 4);
  assert(ALIGN(5,4) == 8);
  assert(ALIGN(19,4) == 20);
  assert(ALIGN(19,8) == 24);
}
