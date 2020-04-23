#include <assert.h>

#include "multiple_stack.h"
#include "min_stack.h"
#include "set_stack.h"
#include "chapter_three.h"

void test_multiple_stacks () {
  int ret = 0;
  
  p_multiple_stack s = create_multiple_stacks(3, 3);

  /* stack 0 size 2 capacity 3
     stack 1 size 0 capacity 3
     stack 2 size 0 capacity 3 */
  push_multiple_stacks(s, 0, 10); push_multiple_stacks(s, 0, 20);
  multiple_stacks_top(s, 0, &ret); assert(ret == 20);
  assert(multiple_stacks_size(s, 0) == 2);
  
  /* stack 0 size 2 capacity 3
     stack 1 size 3 capacity 3
     stack 2 size 0 capacity 3 */
  push_multiple_stacks(s, 1, 40); push_multiple_stacks(s, 1, 30); push_multiple_stacks(s, 1, 40);
  multiple_stacks_top(s, 1, &ret); assert(ret == 40);
  assert(multiple_stacks_size(s, 1) == 3);
  
  /* stack 0 size 2 capacity 3
     stack 1 size 3 capacity 3
     stack 2 size 1 capacity 3 */
  push_multiple_stacks(s, 2, 10);
  multiple_stacks_top(s, 2, &ret); assert(ret == 10);
  assert(multiple_stacks_size(s, 2) == 1);

  /* stack 1 expand
     stack 2 shrink */
  /* stack 0 size 2 capacity 3
     stack 1 size 4 capacity 4
     stack 2 size 1 capacity 2 */
  push_multiple_stacks(s, 1, 60);
  multiple_stacks_top(s, 1, &ret); assert(ret == 60);
  multiple_stacks_top(s, 2, &ret); assert(ret == 10);
  assert(multiple_stacks_size(s, 1) == 4);

  
  /* stack 0 size 2 capacity 3
     stack 1 size 4 capacity 4
     stack 2 size 2 capacity 2 */
  push_multiple_stacks(s, 2, 80);
  assert(multiple_stacks_size(s, 2) == 2);
  multiple_stacks_top(s, 2, &ret); assert(ret == 80);

  /* stack 1 expand
     stack 0 shrink */
  /* stack 0 size 2 capacity 2
     stack 1 size 5 capacity 5
     stack 2 size 1 capacity 2 */
  push_multiple_stacks(s, 1, 90);
  multiple_stacks_top(s, 1, &ret); assert(ret == 90);

  pop_multiple_stacks(s, 0, &ret); assert(ret == 20);
  pop_multiple_stacks(s, 1, &ret); assert(ret == 90);
  pop_multiple_stacks(s, 2, &ret); assert(ret == 80);
  
  free_multiple_stacks(s);
  s = NULL;
  return;
}


void test_min_stack() {
  int val;
  p_min_stack min_stack = min_stack_create();
  min_stack_push(min_stack, 3); min_stack_push(min_stack, 5);   min_stack_push(min_stack, 2);
  assert(min_stack_min(min_stack) == 2);
  min_stack_pop(min_stack,&val);
  assert(min_stack_min(min_stack) == 3);
  min_stack_free(min_stack);
}

void test_set_stack() {
  p_set_stack set_stack = set_stack_create(3);
  set_stack_push(set_stack, 1); set_stack_push(set_stack, 2); set_stack_push(set_stack, 3); set_stack_push(set_stack, 4); set_stack_push(set_stack, 5);
  assert(set_stack_top(set_stack, 1) == 5);  assert(set_stack_top(set_stack, 0) == 3);
  assert(set_stack_pop(set_stack) == 5); assert(set_stack_pop(set_stack) == 4); assert(set_stack_pop(set_stack) == 3);
  assert(set_stack_pop(set_stack) == 2); assert(set_stack_pop(set_stack) == 1);
  set_stack_free(set_stack);
}
