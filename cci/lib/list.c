#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "list.h"

plist list_create(list_type t) {
  plist l = malloc(sizeof(list));
  if(l == 0) return l;
  l->type = t;
  l->head = NULL;
  l->len = 0;
  return l;
}

pnode list_get(plist l, unsigned n) {
  assert(l != NULL && l->type == LIST_TYPE_INTEGER && n <= l->len );
  pnode node = l->head;
  while(--n) {
    node = node->next;
  }
  return node;
}

unsigned long list_get_integer_value(plist l, unsigned n) {
  assert(l != NULL && l->type == LIST_TYPE_INTEGER && n <= l->len );
  pnode node = list_get(l, n);
  return (unsigned long)(node->key);
}

pnode list_push_string(plist l, char* s) {
  assert(l != NULL && l->type == LIST_TYPE_STRING && s != NULL);

  pnode n = malloc(sizeof(node));
  n->key = strdup(s);
  n->value = NULL;
  n->next = NULL;
  
  if(l->head == NULL) {
    l->head = n;
  } else {
    pnode tmp = l->head;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = n; 
  }
  l->len++;
  return n;
}

static pnode list_push_generic(plist l, void* key, void *value, size_t value_len) {
  pnode n = malloc(sizeof(node));
  n->key = key;
  if(value && value_len > 0) {
    n->value = malloc(value_len);
    memcpy(n->value, value, value_len);
  }
  n->next = NULL;
  
  if(l->head == NULL) {
    l->head = n;
  } else {
    pnode tmp = l->head;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = n; 
  }
  l->len++;
  return n;
}

pnode list_push_map(plist l, void* key, void *value, size_t value_len) {
  assert(l != NULL && ((l->type == LIST_TYPE_MAP && value != NULL) || (l->type == LIST_TYPE_SET && value == NULL)));
  return list_push_generic(l, key, value, value_len);
}

pnode list_push_integer(plist l, unsigned long val) {
  assert( l != NULL && l->type == LIST_TYPE_INTEGER);
  return list_push_generic(l, (void*)val, NULL, 0);
}


void list_swap_node(plist l, pnode n1, pnode n2) {
  assert(l && n1 &&n2);
  void * tmp_key = n1->key;
  void * tmp_value = n1->value;

  n1->key = n2->key;
  n1->value = n2->value;

  n2->key = tmp_key;
  n2->value = tmp_value;

  return;  
}

pnode list_remove_node(plist l, pnode p, pnode n) {
  assert(l != NULL && n != NULL);

  pnode t = n->next;
  if(p != NULL)
    p->next = t;

  free(n);
  l->len--;
  return t;
}

void list_free(plist l) {
  assert(l != NULL);
  pnode tmp = l->head;
  while(tmp != NULL) {
    pnode n = tmp->next;
    if(l->type == LIST_TYPE_STRING)
      free(tmp->key);
    else if(l->type == LIST_TYPE_MAP) {
      free(tmp->value);
    }
    free(tmp);
    tmp = n;
  }
  l->head = NULL;
  l->len = 0;
  return;
}

void list_dump(plist l) {
  assert(l != NULL);
  pnode tmp = l->head;
  while(tmp != NULL) {
    if(l->type == LIST_TYPE_STRING)
      printf("%s\r\n", (char*)tmp->key);
    else
      assert(NULL);
    tmp = tmp->next;
  }
  
  return;
}

void list_test() {
  {
    plist l = list_create(LIST_TYPE_STRING);
  
    char input[] = "test this string";
    char* ptr = strtok(input, " ");
    while(ptr != NULL) {
      list_push_string(l, ptr);
      ptr = strtok(NULL, " ");
    }
    
    list_dump(l);
    list_free(l);
    free(l);
  }

  {
    plist l = list_create(LIST_TYPE_INTEGER);

    list_push_integer(l, 1);    list_push_integer(l, 3);     list_push_integer(l, 5);
    assert(l->len == 3 && list_get_integer_value(l, 3) == 5);
    list_free(l);
    free(l);
  }
  return;
}
