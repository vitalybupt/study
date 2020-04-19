#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "varray.h"

static void expand_varray(pvarray a) {
  unsigned int oldcap = a->cap;
  unsigned int newcap = a->cap*2;

  a->val = realloc(a->val, sizeof(char)*newcap);
  memset(a->val+oldcap, 0, oldcap);
  a->cap = newcap;
  return; 
}

pvarray create_varray(){
  pvarray v = malloc(sizeof(varray));
  char *a = malloc(sizeof(char)*INIT_SIZE);
  memset(a, 0, INIT_SIZE);
  v->val = a;
  v->cap = INIT_SIZE;
  v->len = 0;
  return v;  
}

void pushback_varray(pvarray a, char v) {
  assert(a != NULL && a->cap != 0);
  if(a->len == a->cap){
    expand_varray(a);
  }
  a->val[a->len] = v;
  a->len++;
  return;
}

void modifyat_varray(pvarray a, unsigned int pos, char v) {
  assert(a!= NULL && a->cap != 0);
  if(pos >= a->cap) {
    expand_varray(a);
  }
  a->val[pos] = v;
  return;  
}

void free_varray(pvarray a) {
  assert(a != NULL);
  free(a->val);
  a->len = a->cap =0;
  return;
}
