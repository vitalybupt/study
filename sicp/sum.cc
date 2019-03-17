#include <stdio.h>
#include <unistd.h>

// this is a cpp version of 1.3.1 procedure as arguments
// function object is used as lower procedure
// function object is passed as arguments to combine compound higher procedure
class Term {
public:
  Term(){};
  virtual unsigned operator()(unsigned int){};
};

class Next {
public:
  Next(){};
  virtual unsigned operator()(unsigned int){};
};
  
// the higher procedure calculate sigma
// term(a) + term(next(a)) + term(next(next(a)) 
unsigned sum( Term* term, unsigned int a, Next* next, unsigned int b){
  unsigned int i;
  unsigned int ret = 0;
  for(i = a; i<=b; i=next->operator()(i))
    ret += term->operator()(i);
  return ret;
}

class Cubes:public Term {
public:
  Cubes(){};
  unsigned int operator()(unsigned int n){
    unsigned int ret = n*n*n;
    printf("%d\r\n", ret);
    return ret;
  };
};

class Identity:public Term {
public:
  Identity(){};
  unsigned int operator()(unsigned int n){
    unsigned int ret = n;
    printf("%d\r\n", ret);
    return ret;
  };
};

class Increase:public Next {
public:
  Increase(){};
  unsigned int operator()(unsigned int n){
    return n+1;
  };
};

int main(){
  unsigned int ret = 0;
  Cubes cubes;
  Increase increase;
  Identity identity;
  ret = sum(&cubes, 2, &increase, 3);
  printf("result of sum of integral is %d\r\n", ret);
  ret = sum(&identity, 2, &increase, 3);
  printf("result of sum of cubes is %d\r\n", ret);
  return 0;
}
