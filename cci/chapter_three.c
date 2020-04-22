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
    /* member point to data area */
    int *value; /* pointer to linear data area */
    size_t  total_data_size; /* the length of linear data area, in case of int, it is sizeof(int)*stack_total_capacity */

    
    /* information of sperate stack */
    int stack_number; /* number of stacks contained in this multiple stack */
    int original_stack_capacity; /* original stack capacity in unit int */
    int stack_total_capacity; /* the total stack capacity in unit int */

    p_stack_info stack_infos;
} multiple_stack, *p_multiple_stack;

static inline p_stack_info _get_stack_info(p_multiple_stack s, const int stack) {
  return s->stack_infos + stack;
}
static inline int _get_next_stack(p_multiple_stack s, const int stack) {
  return (stack + 1) % (s->stack_number);
}

static bool multiple_stacks_full(p_multiple_stack s, const int stack) {
  p_stack_info s_info = _get_stack_info(s, stack);
  return (s_info->size == s_info->capacity);
}

static p_multiple_stack create_multiple_stacks(const int nums, const int size) {
  if( nums <= 0 || size <= 0) return NULL;
  
  p_multiple_stack stacks = malloc(sizeof(multiple_stack));
  stacks->stack_number = nums;
  stacks->value = malloc(sizeof(unsigned)*nums*size);
  stacks->total_data_size = sizeof(unsigned)*nums*size;
  stacks->stack_total_capacity = nums*size;
  stacks->stack_infos = malloc(sizeof(stack_info)*nums);
  stacks->original_stack_capacity = size;
  
  for(int i = 0; i < nums; ++i){
    (stacks->stack_infos)[i].base = i*size;
    (stacks->stack_infos)[i].size = 0;
    (stacks->stack_infos)[i].capacity = size;
  }
  return stacks;
}

/* get the index of top element */
static int multiple_stacks_latest_index(p_multiple_stack s, int stack) {
    p_stack_info s_info = _get_stack_info(s, stack);
    assert(stack >= 0 && s_info->size);
  
    return (s_info->base + s_info->size - 1) % s->stack_total_capacity;
}

static int multiple_stacks_next_index(p_multiple_stack s, int stack) {
  assert(stack >= 0);
  p_stack_info s_info = _get_stack_info(s, stack);
  return (s_info->base + s_info->size) % s->stack_total_capacity;
}

static bool multiple_stacks_all_full(p_multiple_stack s) {
  for(int i = 0; i < s->stack_number; ++i) {
      p_stack_info s_info = _get_stack_info(s, i);
      if(s_info->size < s_info->capacity)
          return false;
  }
  return true;
}

static void multiple_stacks_move(p_multiple_stack s, const int begin_stack, const int end_stack, const size_t size) {
  p_stack_info s_info_begin = _get_stack_info(s, begin_stack);
  p_stack_info s_info_end = _get_stack_info(s, end_stack);
  int *from = s->value + s_info_begin->base;
  int *dest =  s->value + (s_info_end->base + s_info_end->size) % (s->stack_total_capacity);
  
  if(dest > from) {
      memmove(from + size, from, (dest - from)*sizeof(int));
  } else {
      int tmp = (s->value)[s->stack_total_capacity-1];
      memmove(s->value + 1, s->value, (dest - s->value)*sizeof(int));
      memmove(s->value + s_info_begin->base + 1, s->value + s_info_begin->base, sizeof(int)*(s->stack_total_capacity - s_info_begin->base -1));
      (s->value)[0] = tmp;
  }
  int stack = begin_stack;
  while(stack != end_stack) {
      p_stack_info s_info = _get_stack_info(s, stack);
      s_info->base++;
      stack = _get_next_stack(s, stack);
  }
  s_info_end->base += size;
  s_info_end->capacity -= size;
  
  return;
}


static void multiple_stacks_expand(p_multiple_stack s, const int stack) {
  int from_stack = _get_next_stack(s, stack);
  int to_stack = from_stack;
  
  while(to_stack != stack) {
    if(!multiple_stacks_full(s, to_stack)) {
      multiple_stacks_move(s, from_stack, to_stack, 1);
      _get_stack_info(s, stack)->capacity++;
      return;
    }
    to_stack = _get_next_stack(s, to_stack);
  }
  
  assert(0);
}

static int multiple_stacks_top(p_multiple_stack s, const int num, int *ret) {
  if(num < 0 || num >= s->stack_number)
    return -1;
  int index = multiple_stacks_latest_index(s, num);
  *ret = *(s->value + index);
  return 0;
}

static int multiple_stacks_size(p_multiple_stack s, const int num, int *ret) {
  if(num < 0 || num >= s->stack_number)
    return -1;
  p_stack_info s_info = s->stack_infos + num;
  *ret = s_info->size;
  return 0;
}

static int push_multiple_stacks(p_multiple_stack s, const int num, int val) {
  if(s == NULL || num < 0 || num >= s->stack_number) return -1;
  p_stack_info s_info = s->stack_infos + num;
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

#ifdef DEBUG
static void multiple_stacks_dump_info(p_multiple_stack s) {
    assert(s);
    printf("multiple stacks is:\r\n");
    for(int i = 0; i < s->stack_number; ++i) {
        p_stack_info s_info = _get_stack_info(s, i);
        printf("%d from %d to %d\r\n", i, s_info->base, (s_info->base + s_info->capacity - 1)%s->stack_total_capacity);
    }
    printf("\r\n");
    
    return;
}
#endif

static int pop_multiple_stacks (p_multiple_stack s, const int num, int *top) {
  int ret = multiple_stacks_top(s, num, top);
  if(ret != 0) return ret;
  (s->stack_infos)[num].size -=1;
  return ret;
}

static void free_multiple_stacks(p_multiple_stack s) {
  assert(s);
  free(s->stack_infos);
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
  
