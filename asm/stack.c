#include <stdio.h>

void __attribute__ ((constructor)) a_constructor() { printf("%s\n", __FUNCTION__); }

long mult2(long a, long b){
  long s = a * b;
  return s;
}

void multistore(long x, long y, long *dest){
  long t = mult2(x, y);
  *dest = t;
  return;
}

void main(){
  long val = 0;
  multistore(2, 3, &val);
  return;
}
