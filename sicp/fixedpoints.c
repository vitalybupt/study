#include <stdio.h>
#include <unistd.h>
#include <float.h>
#include <math.h>

typedef double (*pFunction)(double guess);

double f1(double guess){
  return cos(guess);
}

double f2(double guess){
  return cos(guess) + sin(guess);
}

double fixedPoint(pFunction func, double guess){
  if(fabs(func(guess) - guess) <= 0.000001) {
    printf("tolerence is %lf\r\n", fabs(func(guess) - guess));
    return guess;
  }
  return fixedPoint(func, func(guess));
}

// as there is no lambda in C, we can not do as same as lisp. the difference is that
// the lamba is defined in another function
// for lambda, the arguments can be bind in the contexts of a nother function
// as shown in the example below
/* double fixedPoint(pFunction func, unsigned int input, double guess){ */
/*   if(fabs(func(input, guess) - guess) <= 0.000001) { */
/*     printf("tolerence is %lf\r\n", fabs(func(input, guess) - guess)); */
/*     return guess; */
/*   } */
/*   return fixedPoint(func, input, func(input, guess)); */
/* } */

/* double sqart(unsigned input) { */
/*   double f2(double guess) { */
/*   return (guess + input/guess)/2; */
/*   } */
/*   fixedPoint(f2, 2); */
/* } */

void main(){
  double ret = fixedPoint(f1,1);
  printf("%f\r\n", ret);
  ret = fixedPoint(f2,1);
  printf("%f\r\n", ret);
  return;
}
