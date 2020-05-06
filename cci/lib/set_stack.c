#include <stdlib.h>
#include "set_stack.h"

p_set_stack set_stack_create(int capacity) {
  p_set_stack s_stack = malloc(sizeof(set_stack));
  s_stack->stacks = list_create(LIST_TYPE_GENERIC);
  s_stack->capacity = capacity;
  s_stack->size = 0;

  int *stack = malloc(sizeof(int)*capacity);
  list_push_back_generic(s_stack->stacks, stack);
  return s_stack;
}

void set_stack_push(p_set_stack s_stack, int val) {
  int* stack = list_end(s_stack->stacks)->key;
  stack[s_stack->size] = val;
  if(s_stack->size == s_stack->capacity) {
    int* new_stack = malloc(sizeof(int)*s_stack->capacity);
    list_push_back_generic(s_stack->stacks, new_stack);
    s_stack->size = 0;
    return;
  }
  s_stack->size += 1;
  return;
  
}

int set_stack_pop(p_set_stack s_stack) {
  int ret;
  do {
      int* stack = list_end(s_stack->stacks)->key;
      if(s_stack->size == 0) {
	free(stack);
	list_pop_back_generic(s_stack->stacks);
	stack = list_end(s_stack->stacks)->key;
	s_stack->size = s_stack->capacity;
      } 
      ret = stack[s_stack->size-1];
      s_stack->size -= 1;
  } while(0);

  return ret;  
}

int set_stack_top(p_set_stack s_stack, int number) {
  int ret;
  do {
    int *stack = list_get_generic(s_stack->stacks, number);
    if(number == (s_stack->stacks->len -1))
      ret = stack[s_stack->size - 1];
    else
      ret = stack[s_stack->capacity -1];
  }while(0);

  return ret;
}

void set_stack_free(p_set_stack s_stack) {
  list_free(s_stack->stacks);
  free(s_stack);
  return;
}
