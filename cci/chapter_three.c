#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "chapter_three.h"

typedef struct {
  unsigned base;
  unsigned capacity;
  unsigned size;
} stack_info, *p_stack_info;

typedef struct {
  p_stack_info info;
  int number;
  int total_capacity;
  int *value;
} multiple_stack, *p_multiple_stack;

static p_stack_info _get_stack_info(p_multiple_stack s, const int stack_index) {
  return s->info + stack_index;
}
static inline int _get_next_stack_index(p_multiple_stack s, const int stack_index) {
  return (stack_index + 1) % (s->number);
}

static bool multiple_stacks_full(p_multiple_stack s, const int stack_index) {
  p_stack_info s_info = _get_stack_info(s, stack_index);
  return (s_info->size == s_info->capacity);
}

static p_multiple_stack create_multiple_stacks(const int nums, const int size) {
  if( nums <= 0 || size <= 0) return NULL;
  
  p_multiple_stack stacks = malloc(sizeof(multiple_stack));
  stacks->number = nums;
  stacks->value = malloc(sizeof(unsigned)*nums*size);
  stacks->total_capacity = nums*size;
  stacks->info = malloc(sizeof(stack_info)*nums);
  for(int i = 0; i < nums; ++i){
    (stacks->info)[i].base = i*size;
    (stacks->info)[i].size = 0;
    (stacks->info)[i].capacity = size;
  }
  return stacks;
}

/* get the index of top element */
static int multiple_stacks_latest_index(p_multiple_stack s, int num) {
  assert(num >= 0);
  p_stack_info s_info = s->info + num;
  assert(s_info->size > 0);
  return (s_info->base + s_info->size - 1) % s->total_capacity;
}

static int multiple_stacks_next_index(p_multiple_stack s, int num) {
  assert(num >= 0);
  p_stack_info s_info = s->info + num;
  return (s_info->base + s_info->size) % s->total_capacity;
}

static bool multiple_stacks_all_full(p_multiple_stack s) {
  for(int i = 0; i < s->number; ++i) {
    p_stack_info s_info = s->info + i;
    if(s_info->size < s_info->capacity)
      return false;
  }
  return true;
}

static void multiple_stacks_move(p_multiple_stack s, const int begin_stack_index, const int end_stack_index, const size_t size) {
  p_stack_info s_info_begin = _get_stack_info(s, begin_stack_index);
  p_stack_info s_info_end = _get_stack_info(s, end_stack_index);
  int *from = s->value + s_info_begin->base;
  int *to =  s->value + (s_info_end->base + s_info_end->size) % (s->total_capacity);
  
  if(to > from) {
    memmove(from + 1, from, to-from);
  } else {
    memmove(s->value + 1, s->value, to - s->value);
    (s->value)[0] = (s->value)[s->total_capacity-1];
    for(int i = from_stack_index; i < s->number; ++i) {
      p_stack_info info = s->info + i;
      info->base++;
    }
    memmove(s->value + s_from_info->base + 1, s->value + s_from_info->base, sizeof(int)*(s->total_capacity - s_from_info->base -1));
  }
  s_cur_info->base++;
  s_cur_info->capacity--;  
  return;
}


static void multiple_stacks_expand(p_multiple_stack s, const int stack_index) {
  int from_stack_index = _get_next_stack_index(s, stack_index);
  p_stack_info from_stack_info = _get_stack_info(from_stack_index)
      
  int to_stack_index = from_stack_index;
  while(to_stack_index != stack_index) {
    if(!multiple_stacks_full(s, to_stack_index)) {
      multiple_stacks_move(s, from_stack_index, to_stack_index, 1);
      break;
    }
    to_stack_index = _get_next_stack_index(s, to_stack_index);
  }
  _get_stack_info(stack_index)->capacity++;
  return;
}

static int multiple_stacks_top(p_multiple_stack s, const int num, int *ret) {
  if(num < 0 || num >= s->number)
    return -1;
  int index = multiple_stacks_latest_index(s, num);
  *ret = *(s->value + index);
  return 0;
}

static int multiple_stacks_size(p_multiple_stack s, const int num, int *ret) {
  if(num < 0 || num >= s->number)
    return -1;
  p_stack_info s_info = s->info + num;
  *ret = s_info->size;
  return 0;
}

static int push_multiple_stacks(p_multiple_stack s, const int num, int val) {
  if(s == NULL || num < 0 || num >= s->number) return -1;
  p_stack_info s_info = s->info + num;
  if(s_info->size >= s_info->capacity) {
    if(multiple_stacks_all_full(s))
      return -1;
    multiple_stacks_expand(s, num);
  }
  const unsigned index = multiple_stacks_next_index(s, num);
  (s->value)[index] = val;
  s_info->size +=1;
  return 0;
}

static int pop_multiple_stacks (p_multiple_stack s, const int num, int *top) {
  int ret = multiple_stacks_top(s, num, top);
  if(ret != 0) return ret;
  (s->info)[num].size -=1;
  return ret;
}

static void free_multiple_stacks(p_multiple_stack s) {
  assert(s);
  free(s->info);
  free(s->value);
  free(s);
  return;  
}

void multiple_stacks () {
  int ret = 0;
  
  p_multiple_stack s = create_multiple_stacks(3, 3);

  /* stack 0 size 2 capacity 3
     stack 1 size 0 capacity 3
     stack 2 size 0 capacity 3 */
  push_multiple_stacks(s, 0, 10); push_multiple_stacks(s, 0, 20);
  multiple_stacks_top(s, 0, &ret); assert(ret == 20);
  multiple_stacks_size(s, 0, &ret); assert(ret == 2);
  
  /* stack 0 size 2 capacity 3
     stack 1 size 3 capacity 3
     stack 2 size 0 capacity 3 */
  push_multiple_stacks(s, 1, 40); push_multiple_stacks(s, 1, 30); push_multiple_stacks(s, 1, 40);
  multiple_stacks_top(s, 1, &ret); assert(ret == 40);
  multiple_stacks_size(s, 1, &ret); assert(ret == 3);
  
  /* stack 0 size 2 capacity 3
     stack 1 size 3 capacity 3
     stack 2 size 1 capacity 3 */
  push_multiple_stacks(s, 2, 10);
  multiple_stacks_top(s, 2, &ret); assert(ret == 10);
  multiple_stacks_size(s, 2, &ret); assert(ret == 1);

  /* stack 1 expand
     stack 2 shrink */
  /* stack 0 size 2 capacity 3
     stack 1 size 4 capacity 4
     stack 2 size 1 capacity 2 */
  push_multiple_stacks(s, 1, 60);
  multiple_stacks_top(s, 1, &ret); assert(ret == 60);
  multiple_stacks_top(s, 2, &ret); assert(ret == 10);
  multiple_stacks_size(s, 1, &ret); assert(ret == 4);
  
  /* stack 0 size 2 capacity 3
     stack 1 size 4 capacity 4
     stack 2 size 2 capacity 2 */
  push_multiple_stacks(s, 2, 80);
  multiple_stacks_size(s, 2, &ret); assert(ret == 2);
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
  
