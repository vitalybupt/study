#ifndef LIST_H
#define LIST_H
#include <stddef.h>
#include <stdbool.h>

typedef enum {
      LIST_TYPE_INTEGER,
      LIST_TYPE_STRING,
      LIST_TYPE_MAP,
      LIST_TYPE_SET,
      LIST_TYPE_GENERIC      
} list_type;
  
typedef struct node {
  struct node *next;
  void *key;
  void *value;
} node, *p_node;

typedef struct list {
  p_node head;
  p_node tail;
  unsigned len;
  list_type type;
} list, *p_list;

p_list list_create(list_type t);

p_node list_push_back_generic(p_list l, void* val);
p_node list_push_back_string(p_list l, char* val);
p_node list_push_back_integer(p_list l, unsigned long val);
p_node list_push_back_map(p_list l, void *key, void *value, size_t value_len);

void* list_pop_back_generic(p_list l);

p_node list_push_front_generic(p_list l, void* val);
p_node list_push_front_string(p_list l, char* val);
p_node list_push_front_integer(p_list l, unsigned long val);
p_node list_push_front_map(p_list l, void *key, void *value, size_t value_len);

p_node list_get(p_list l, unsigned n);
p_node list_begin(p_list l);
p_node list_end(p_list l);
void* list_begin_generic(p_list l);
void* list_end_generic(p_list l);

unsigned long list_get_integer_value(p_list l, unsigned n);

bool list_empty(p_list l);
void list_update_size(p_list l);
void list_swap_node(p_list l, p_node n1, p_node n2);
p_node list_remove_node(p_list l, p_node p, p_node n);
void list_dump(p_list l);
void list_free(p_list l);

void list_test();
#endif
