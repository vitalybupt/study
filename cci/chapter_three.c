#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "multiple_stack.h"
#include "min_stack.h"
#include "set_stack.h"
#include "stack.h"
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

typedef struct {
  p_multiple_stack push_stack;
  p_multiple_stack pop_stack;
  int size;
} queue, *p_queue;

static p_queue create_queue(int size) {
  p_queue q = malloc(sizeof(queue));
  q->push_stack = create_multiple_stacks(1, size);
  q->pop_stack = create_multiple_stacks(1, size);
  q->size = 0;

  return q;
}

static void queue_push(p_queue q, int value) {
  push_multiple_stacks(q->push_stack, 0, value);
  q->size++;
  return;
}

static int queue_pop(p_queue q) {
  int tmp = 0;
  if(multiple_stacks_size(q->pop_stack, 0) > 0) {
    q->size--;
    pop_multiple_stacks(q->pop_stack, 0, &tmp);
  } else {
    while(multiple_stacks_size(q->push_stack, 0) > 1) {
      pop_multiple_stacks(q->push_stack, 0, &tmp);
      push_multiple_stacks(q->pop_stack, 0, tmp);
    }
    q->size --;
    pop_multiple_stacks(q->push_stack, 0, &tmp);
  }
  return tmp;
}

static void free_queue(p_queue q) {
  free_multiple_stacks(q->push_stack);
  free_multiple_stacks(q->pop_stack);
  free(q);
  return;
}

void test_myqueue() {
  p_queue q = create_queue(16);
  queue_push(q, 1);
  queue_push(q, 2);
  queue_push(q, 3);
  assert(queue_pop(q) == 1);
  assert(queue_pop(q) == 2);
  assert(queue_pop(q) == 3);
  free_queue(q);
  return;  
}


static void sort_stack(p_stack s) {
  do {
    p_stack sort = stack_create(stack_size(s));
    while(!stack_empty(s)) {
      int value_top;
      int sort_top;
      stack_top(s, &value_top);
	
      if(stack_empty(sort)) {
	int tmp;
	stack_pop(s, &tmp);
	stack_push(sort, tmp);
      } else {
	stack_top(sort, &sort_top);
	if(value_top >= sort_top) {
	  int tmp;
	  stack_pop(s, &tmp);
	  stack_push(sort, tmp);
	  continue;
	}
	
	int id = stack_size(sort) - 1;
	for(; id >= 0; --id) {
	  int sort_stack_value;
	  stack_peek(sort, id, &sort_stack_value);
	  if(value_top < sort_stack_value) {
	    continue;
	  }
	  break;
	}
	int sort_stack_pop_times = stack_size(sort) - id - 1;
	int tmp1;
	stack_pop(s, &tmp1);

	for(int i = 0; i < sort_stack_pop_times; ++i) {
	  int tmp;
	  stack_pop(sort, &tmp);
	  stack_push(s, tmp);
	}
	
	stack_push(sort, value_top);
	for(int i = 0; i < sort_stack_pop_times; ++i) {
	  int tmp;
	  stack_pop(s, &tmp);
	  stack_push(sort, tmp);
	}
      }
    }

    while(!stack_empty(sort)) {
      int tmp;
      stack_pop(sort,  &tmp);
      stack_push(s, tmp);
    }
    stack_free(sort);    
  }while(0);
  return;
}

void test_sort_stack() {
  p_stack s = stack_create(16);
  stack_push(s, 3);   stack_push(s, 6);   stack_push(s, 1);   stack_push(s, 5);   stack_push(s, 4);
  sort_stack(s);

  int min;
  stack_pop(s, &min);
  assert(min == 1);
  stack_pop(s, &min);
  assert(min == 3);
  stack_pop(s, &min);
  assert(min == 4);
  stack_pop(s, &min);
  assert(min == 5);
  stack_pop(s, &min);
  assert(min == 6);

  stack_free(s);

  return;
}

typedef enum {
      DOG,
      CAT
} ANIMAL_TYPE;
  
typedef struct {
  char* name;
  time_t ts;
}animal, *p_animal;

typedef struct {
  p_list dog_list;
  p_list cat_list;
} animal_shelter, *p_animal_shelter;

static p_animal_shelter animal_shelter_create() {
  p_animal_shelter s = malloc(sizeof(animal_shelter));
  s->dog_list = list_create(LIST_TYPE_GENERIC);
  s->cat_list = list_create(LIST_TYPE_GENERIC);
  return s;
}

static void animal_shelter_enqueue(p_animal_shelter s, ANIMAL_TYPE type, char *name) {
  p_animal a = malloc(sizeof(animal));
  a->name = strdup(name);
  
  struct timeval tv;
  gettimeofday(&tv, NULL);
  a->ts = tv.tv_sec*100000 + tv.tv_usec;
  switch(type) {
  case DOG:
    list_push_front_generic(s->dog_list, a);
    break;
  case CAT:
    list_push_front_generic(s->cat_list, a);
    break;
  default:
    assert(0);
  }
  return;  
}

static p_animal dequeue(p_animal_shelter s) {
  p_animal dog = list_end_generic(s->dog_list);
  p_animal cat = list_end_generic(s->cat_list);

  if(dog->ts > cat->ts) {
    return list_pop_back_generic(s->cat_list);
  } else {
    return list_pop_back_generic(s->dog_list);
  }
}

static p_animal dequeue_dog (p_animal_shelter s) {
  return list_pop_back_generic(s->dog_list);
}

static p_animal dequeue_cat (p_animal_shelter s) {
  return list_pop_back_generic(s->cat_list);
}

static void animal_shelter_free(p_animal_shelter s) {
  list_free(s->dog_list);
  list_free(s->cat_list);
  free(s);
  return;
}

void test_animal_sheleter() {
  p_animal_shelter s = animal_shelter_create();
  animal_shelter_enqueue(s, DOG, "dog1");
  usleep(1);
  animal_shelter_enqueue(s, CAT, "cat1");
  usleep(1);
  animal_shelter_enqueue(s, DOG, "dog2");
  usleep(1);
  animal_shelter_enqueue(s, CAT, "cat2");
  p_animal a = dequeue_dog(s);
  assert(strcmp(a->name, "dog1") == 0);
  free(a->name);
  free(a);

  p_animal a2 = dequeue(s);
  assert(strcmp(a2->name, "cat1") == 0);
  free(a2->name);
  free(a2);

  p_animal a3 = dequeue_cat(s);
  assert(strcmp(a3->name, "cat2") == 0);
  free(a3->name);
  free(a3);
  
  animal_shelter_free(s);
  return;
}
