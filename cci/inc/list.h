#ifndef LIST_H
#define LIST_H
#include <stddef.h>

typedef enum {
      LIST_TYPE_INTEGER,
      LIST_TYPE_STRING,
      LIST_TYPE_MAP,
      LIST_TYPE_SET
} list_type;
  
typedef struct node {
  struct node *next;
  void *key;
  void *value;
} node, *pnode;

typedef struct list {
  pnode head;
  pnode tail;
  unsigned int len;
  list_type type;
} list, *plist;

plist list_create(list_type t);

pnode list_push_back_string(plist l, char* val);
pnode list_push_back_integer(plist l, unsigned long val);
pnode list_push_back_map(plist l, void *key, void *value, size_t value_len);

pnode list_push_front_string(plist l, char* val);
pnode list_push_front_integer(plist l, unsigned long val);
pnode list_push_front_map(plist l, void *key, void *value, size_t value_len);

pnode list_get(plist l, unsigned n);
unsigned long list_get_integer_value(plist l, unsigned n);

void list_update_size(plist l);
void list_swap_node(plist l, pnode n1, pnode n2);
pnode list_remove_node(plist l, pnode p, pnode n);
void list_dump(plist l);
void list_free(plist l);

void list_test();
#endif
