#include <stdio.h>
#include <unistd.h>

int isPrime(int number) {
  unsigned int i;
  for(i = 2; i*i <= number; ++i) {
    if(number % i == 0) return 0;
  }
  
  return 1;
}

void iterative(int upper) {
  int i = 0;
  for(i = upper; i >= 1; --i) {
    int j = 0;
    for (j = i - 1; j >= 1; --j) {
      if(isPrime(j+i))
        printf("(%d, %d):%d\r\n", j, i, j+i);
    }
  }
}

void recursive(int upper) {
  if(upper == 1)
    printf("1\n");
  else {
    printf("%d ",upper);
    recursive(upper -1 );
  }
}
int main() {
  iterative(6);
  //recursive(6);
  return 0;
}
