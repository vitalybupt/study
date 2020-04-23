#ifndef MULTIPLE_STACK_H
#define MULTIPLE_STACK_H
#include <stdlib.h>

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

p_multiple_stack create_multiple_stacks(const int nums, const int size);
int multiple_stacks_top(p_multiple_stack s, const int num, int *ret);
int multiple_stacks_peek(p_multiple_stack s, const int num, int pos, int *val);
int push_multiple_stacks(p_multiple_stack s, const int num, int val);
int pop_multiple_stacks (p_multiple_stack s, const int num, int *top);
int multiple_stacks_size(p_multiple_stack s, const int num);
void free_multiple_stacks(p_multiple_stack s);
#endif
