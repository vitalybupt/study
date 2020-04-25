#include "stack.h"

p_stack stack_create(const int size) {
  return create_multiple_stacks(1, size);
}

int stack_top(p_stack s,  int *ret) {
  return multiple_stacks_top(s, 0, ret);  
}

int stack_push(p_stack s, int val) {
  return push_multiple_stacks(s, 0, val);
}

int stack_pop(p_stack s, int *top){
  return pop_multiple_stacks (s, 0, top);
}

int stack_size(p_stack s) {
  return multiple_stacks_size(s, 0);
}

bool stack_empty(p_stack s) {
  return multiple_stacks_empty(s, 0);
}

int stack_peek(p_stack s, int pos, int *val) {
  return multiple_stacks_peek(s, 0, pos, val);
}

void stack_free(p_stack s) {
  free_multiple_stacks(s);
  return;
}
