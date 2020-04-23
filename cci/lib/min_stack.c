#include "min_stack.h"

p_min_stack min_stack_create() {
  p_min_stack m_stack = malloc(sizeof(min_stack));
  m_stack->value_stack = create_multiple_stacks(1, 16);
  m_stack->min_stack = create_multiple_stacks(1, 16);
  return m_stack;
}

int min_stack_push(p_min_stack s, int v) {
  int ret = 0;
  do {
    ret = push_multiple_stacks(s->value_stack, 0, v);
    if(!ret)
      break;
    int min;
    multiple_stacks_top(s->min_stack, 0, &min);
    if(v < min)
      push_multiple_stacks(s->min_stack, 0, ret);
  } while(0);
  
  return ret;
}

int min_stack_pop(p_min_stack s, int *val) {
  int ret = 0;
  do {
    int min_pos;
    if(!(ret = multiple_stacks_top(s->min_stack, 0, &min_pos)))
      break;
    if(min_pos == (multiple_stacks_size(s->value_stack, 0) - 1))
      pop_multiple_stacks(s->min_stack, 0,  &min_pos);
    pop_multiple_stacks(s->value_stack, 0, val);
  } while(0);
  return ret;
}

int min_stack_min(p_min_stack s) {
  int min;
  int min_pos;
  do {
    multiple_stacks_top(s->min_stack, 0, &min_pos);
    multiple_stacks_peek(s->value_stack, 0, min_pos, &min);
  } while(0);
  return min;
}
void min_stack_free(p_min_stack s) {
  free_multiple_stacks(s->value_stack);
  free_multiple_stacks(s->min_stack);
  free(s);
  return;
}


