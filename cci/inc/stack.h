#ifndef STACK_H
#define STACK_H
#include "multiple_stack.h"

typedef multiple_stack stack;
typedef p_multiple_stack p_stack;

p_stack stack_create(const int size);
int stack_top(p_stack s,  int *ret);
int stack_push(p_stack s, int val);
int stack_pop(p_stack s, int *top);
int stack_size(p_stack s);
bool stack_empty(p_stack s);
int stack_peek(p_stack s, int pos, int *val);
void stack_free(p_stack s);
#endif
  
