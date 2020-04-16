#include "hard.h"

void swap_unsigned(unsigned *a, unsigned *b){
  *a = (*a)^(*b);
  *b = (*a)^(*b);
  *a = (*a)^(*b);
}
