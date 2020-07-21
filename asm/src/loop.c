long pcount_while(unsigned long x){
  long result = 0;
  do{
    result += x & 0x01;
    x = x >> 1;
  } while(x);
  return result;
}

long pcount_goto(unsigned long x){
  long result = 0;
 loop:
  result += x & 0x01;
  x = x >> 1;
  if(x) goto loop;
  return result;
}
