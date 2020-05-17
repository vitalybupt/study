#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "arraylist.h"

pArrayList create_arraylist() {
    pArrayList a = malloc(sizeof(ArrayList));
    a->val = malloc(sizeof(void*)*INIT_SIZE);
    a->strlen = 0;
    a->size = 0;
    a->cap = INIT_SIZE;

    return a;
}

void arraylist_append_string(pArrayList a, const char* s) {
    if(a->size >= a->cap) {
        a->val = realloc(a->val, sizeof(void*)*(a->cap)*2);
        a->cap *= 2;
    }
    a->val[a->size] = strdup(s);
    a->strlen +=strlen(s);
    a->size++;
    
    return;
}

void arraylist_append_generic(pArrayList a, void* s) {
    if(a->size >= a->cap) {
        a->val = realloc(a->val, sizeof(void*)*(a->cap)*2);
        a->cap *= 2;
    }
    a->val[a->size] = s;
    a->size++;
    return;
}

void* arraylist_get(pArrayList a, int i) {
  if((unsigned)i >= (unsigned)a->size) return NULL;
  return a->val[i];
}

void free_arraylist(pArrayList a) {
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

unsigned int arraylist_get_strlen(pArrayList a) {
  assert(a != NULL);
  return a->strlen;
}

char* arraylist_tostring(pArrayList a) {
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
  pArrayList strings = create_arraylist();
  arraylist_append_string(strings, "this");
  arraylist_append_string(strings, " is test");
  arraylist_append_string(strings, " for strings");
  char* cstr_strings = arraylist_tostring(strings);
  
  assert(cstr_strings && strcmp(cstr_strings, "this is test for strings") == 0);

  for(int i = 0; i < 17; ++i)
      arraylist_append_string(strings, "test");
  arraylist_append_string(strings, "test");
  free(cstr_strings);
  free_arraylist(strings);
  free(strings);

  return;
}
