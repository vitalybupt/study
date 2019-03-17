#include <stdio.h>
#include <unistd.h>

// this is a c version of 1.3.1 procedure as arguments
// function pointer is used as lower procedure
// function pointer is passed as arguments to combine compound higher procedure
typedef unsigned int (*type_term)(unsigned int n);
typedef unsigned int (*type_next)(unsigned int n);

// the higher procedure calculate sigma
// term(a) + term(next(a)) + term(next(next(a)) 
unsigned sum(type_term term, unsigned int a, type_next next, unsigned int b){
  unsigned int i;
  unsigned int ret = 0;
  for(i = a; i<=b; i=next(i))
    ret += term(i);
  return ret;
}

unsigned int cubes(unsigned int n) {
  unsigned int ret = n*n*n;
  printf("%d\r\n", ret);
  return ret;
}

unsigned int increase(unsigned int n) {
  return n+1;
}

unsigned int identity(unsigned int n) {
  unsigned int ret = n;
  printf("%d\r\n",ret);
  return ret;
}

void main(){
  unsigned int ret = 0;
  ret = sum(cubes, 2, increase, 3);
  printf("result of sum of integral is %d\r\n", ret);
  ret = sum(identity, 2, increase, 3);
  printf("result of sum of cubes is %d\r\n", ret);
  return;
}
