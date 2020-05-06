#ifndef SET_STACK_H
#define SET_STACK_H

#include "list.h"

typedef struct  {
  p_list stacks;
  int capacity;
  int size;
} set_stack, *p_set_stack;

p_set_stack set_stack_create(int capacity);
void set_stack_push(p_set_stack s_stack, int val);
int set_stack_pop(p_set_stack s_stack);
int set_stack_top(p_set_stack s, int number);
void set_stack_free(p_set_stack s_stack);
#endif
