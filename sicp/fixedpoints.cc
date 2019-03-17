#include <stdio.h>
#include <unistd.h>
#include <float.h>
#include <math.h>

class Term {
public:
  Term(){};
  virtual double operator()(double){};
};

class COS:public Term {
public:
  COS(){};
  double operator()(double guess) {return cos(guess);};
};

class SINCOS:public Term {
public:
  SINCOS(){};
  double operator()(double guess) {return cos(guess) + sin(guess);};
};

class SQRT:public Term {
public:
  SQRT(unsigned int n){input = n;};
  double operator()(double guess) {return (guess + input/guess)/2;};
private:
  unsigned input;
};

double fixedPoint(Term* term, double guess){
  double tolerence = fabs(term->operator()(guess) - guess);
  if( tolerence <= 0.000001) {
    printf("tolerence is %lf\r\n", tolerence);
    return guess;
  }
  return fixedPoint(term, term->operator()(guess));
}

int main(){
  COS fcos;
  double ret = fixedPoint(&fcos,1);
  printf("%f\r\n", ret);
  SINCOS fsincos;
  ret = fixedPoint(&fsincos,1);
  printf("%f\r\n", ret);
  SQRT fsqrt(2); // function object support some kind of run time binding so it can be regarded as a replacement of lambda
  ret = fixedPoint(&fsqrt,1);
  printf("%f\r\n", ret);
  return 0;
}
