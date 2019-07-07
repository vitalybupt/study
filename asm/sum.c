long plus(long x, long y){
  return x+y;
}

void sumstore(long x, long y, long* dest){
  long t = plus(x, y);
  *dest = t;
  return;
}
void main()
{
  long result = 0;
  sumstore(1, 2, &result);
  return;
}
