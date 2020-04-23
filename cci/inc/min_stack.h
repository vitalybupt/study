#include "multiple_stack.h"

typedef struct {
  p_multiple_stack value_stack;
  p_multiple_stack min_stack;
} min_stack, *p_min_stack;

p_min_stack min_stack_create();
int min_stack_push(p_min_stack s, int v);
int min_stack_pop(p_min_stack s, int *val);
int min_stack_min(p_min_stack s);
void min_stack_free(p_min_stack);
