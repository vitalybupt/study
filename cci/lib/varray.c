#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "varray.h"

static void _varray_expand(p_varray a) {
  unsigned int oldcap = a->cap;
  unsigned int newcap = a->cap*2;

  a->val = realloc(a->val, sizeof(char)*newcap);
  memset(a->val+oldcap, 0, oldcap);
  a->cap = newcap;
  return; 
}

extern char* varray_get_string(p_varray a);

p_varray varray_create(){
  p_varray v = malloc(sizeof(varray));
  char *a = malloc(sizeof(char)*INIT_SIZE);
  memset(a, 0, INIT_SIZE);
  v->val = a;
  v->cap = INIT_SIZE;
  v->len = 0;
  return v;  
}

p_varray varray_clone(p_varray o) {
  p_varray n = malloc(sizeof(varray));
  memcpy(n, o, sizeof(varray));

  n->val = malloc(sizeof(char)*(n->cap));
  memcpy(n->val, o->val, sizeof(char)*(n->cap));
  return n;
}

void varray_append_char(p_varray a, char v) {
  assert(a != NULL && a->cap != 0);
  if(a->len == a->cap){
    _varray_expand(a);
  }
  a->val[a->len] = v;
  a->len++;
  return;
}

void varray_modify(p_varray a, unsigned int pos, char v) {
  assert(a!= NULL && a->cap != 0);
  if(pos >= a->cap) {
    _varray_expand(a);
  }
  a->val[pos] = v;
  return;  
}

void varray_free(p_varray a) {
  assert(a != NULL);
  free(a->val);
  a->len = a->cap =0;
  return;
}
