#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "arraylist.h"

int arraylist_get_size(p_arraylist a);

p_arraylist arraylist_create() {
    p_arraylist a = malloc(sizeof(ArrayList));
    a->val = malloc(sizeof(void*)*INIT_SIZE);
    a->strlen = 0;
    a->size = 0;
    a->cap = INIT_SIZE;

    return a;
}

p_arraylist arraylist_clone(p_arraylist o) {
  p_arraylist n = malloc(sizeof(ArrayList));
  memcpy(n, o, sizeof(ArrayList));
  n->val = malloc(sizeof(void*)*(o->cap));
  for(int i = 0; i < n->size; ++i) {
    n->val[i] = strdup(o->val[i]);
  }
  return n;
}

void arraylist_append_string(p_arraylist a, const char* s) {
    if(a->size >= a->cap) {
        a->val = realloc(a->val, sizeof(void*)*(a->cap)*2);
        a->cap *= 2;
    }
    a->val[a->size] = strdup(s);
    a->strlen +=strlen(s);
    a->size++;
    
    return;
}

void arraylist_insert_string(p_arraylist a, int p, const char* s) {
  if(a->size >= a->cap) {
    a->val = realloc(a->val, sizeof(void*)*(a->cap)*2);
    a->cap *= 2;
  }
  memmove(a->val+p+1, a->val+p, sizeof(void*)*(a->size - p));
  a->val[p] = strdup(s);
  a->strlen +=strlen(s);
  a->size++;
}

void arraylist_append_generic(p_arraylist a, void* s) {
    if(a->size >= a->cap) {
        a->val = realloc(a->val, sizeof(void*)*(a->cap)*2);
        a->cap *= 2;
    }
    a->val[a->size] = s;
    a->size++;
    return;
}

void* arraylist_pop_back_generic(p_arraylist a) {
  void *ret = NULL;

  do {
    if(a->size == 0) break;
    ret = a->val[a->size - 1];
    a->size--;
  }while(0);
  
  return ret;
}

bool arraylist_empty(p_arraylist a);

void* arraylist_peak(p_arraylist a, int i) {
  if((unsigned)i >= (unsigned)a->size) return NULL;
  return a->val[i];
}

void arraylist_free(p_arraylist a) {
    for(int i = 0; i < a->size; ++i) {
        free(a->val[i]);
    }
    free(a->val);
    a->val = NULL;
    a->strlen = 0;
    a->size = 0;
    a->cap = 0;
    return;
}

unsigned int arraylist_get_strlen(p_arraylist a) {
  assert(a != NULL);
  return a->strlen;
}

char* arraylist_tostring(p_arraylist a) {
  char *str = NULL;
  do {
    if(a->strlen == 0)
      break;

    str = calloc(a->strlen+1, sizeof(char));

    unsigned int sublen = 0;
    
    for(int i = 0; i < a->size; ++i) {
        memmove(str+sublen, a->val[i], strlen(a->val[i]));
        sublen += strlen(a->val[i]);
    }
  } while(0);

  return str; 
}

void stringbuilder_test() {
  p_arraylist strings = arraylist_create();
  arraylist_append_string(strings, "this");
  arraylist_append_string(strings, " is test");
  arraylist_append_string(strings, " for strings");
  char* cstr_strings = arraylist_tostring(strings);
  
  assert(cstr_strings && strcmp(cstr_strings, "this is test for strings") == 0);

  for(int i = 0; i < 17; ++i)
      arraylist_append_string(strings, "test");
  arraylist_append_string(strings, "test");
  free(cstr_strings);
  arraylist_free(strings);
  free(strings);

  return;
}
