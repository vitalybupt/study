#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "list.h"

p_list list_create(list_type t) {
  p_list l = malloc(sizeof(list));
  if(l == 0) return l;
  l->type = t;
  l->head = NULL;
  l->len = 0;
  return l;
}

void list_update_size(p_list l) {
    unsigned len = 0;
    p_node n = l->head;
    while(n) {
        n = n->next;
        ++len;
    }
    l->len = len;
    return;
}

static p_node _list_get(p_list l, unsigned n) {
  p_node node = l->head;
  while(--n) {
    node = node->next;
  }
  return node;
}

p_node list_get(p_list l, unsigned n) {
  return _list_get(l, n);
}

unsigned long list_get_integer_value(p_list l, unsigned n) {
  assert(l != NULL && l->type == LIST_TYPE_INTEGER && n <= l->len );
  p_node node = _list_get(l, n);
  return (unsigned long)(node->key);
}

void* list_get_generic(p_list l, unsigned n) {
  assert(l != NULL && l->type == LIST_TYPE_GENERIC && n <= l->len );
  p_node node = _list_get(l, n);
  return node->key;
}

p_node list_begin(p_list l) {
  assert(l != NULL);
  return l->head;
}
p_node list_end(p_list l) {
  assert(l != NULL);
  return l->tail;
}

void* list_begin_generic(p_list l) {
  return l->head->key;
}
void* list_end_generic(p_list l) {
  return l->tail->key;
}

static p_node _list_push_back_generic(p_list l, void* key, void *value, size_t value_len) {
  p_node n = malloc(sizeof(node));
  n->key = key;
  if(value && value_len > 0) {
    n->value = malloc(value_len);
    memcpy(n->value, value, value_len);
  }
  n->next = NULL;
  
  if(l->head == NULL) {
    l->head = l->tail = n;
  } else {
    l->tail->next = n;
    l->tail = n;
  }
  l->len++;
  return n;
}

p_node list_push_back_generic(p_list l, void* s) {
  assert(l != NULL && l->type == LIST_TYPE_GENERIC && s != NULL);
  return _list_push_back_generic(l, s, NULL, 0);
}

p_node list_push_back_string(p_list l, char* s) {
  assert(l != NULL && l->type == LIST_TYPE_STRING && s != NULL);
  return _list_push_back_generic(l, (void*)strdup(s), NULL, 0);
}

p_node list_push_back_map(p_list l, void* key, void *value, size_t value_len) {
  assert(l != NULL && ((l->type == LIST_TYPE_MAP && value != NULL) || (l->type == LIST_TYPE_SET && value == NULL)));
  return _list_push_back_generic(l, key, value, value_len);
}

p_node list_push_back_integer(p_list l, unsigned long val) {
  assert( l != NULL && l->type == LIST_TYPE_INTEGER);
  return _list_push_back_generic(l, (void*)val, NULL, 0);
}

void* list_pop_back_generic(p_list l) {
  assert(l && l->tail);
  void* ret;
  do {
    if(l->len == 1) {
      ret = l->tail->key;
      free(l->tail);
      l->head = l->tail = NULL;
    } else {
      p_node iterator = l->head;
      while(iterator->next->next) {
	iterator = iterator->next;
      }
      l->tail = iterator;
      ret = l->tail->next->key;
      free(l->tail->next);
      l->tail->next = NULL;
    }
  }while(0);
  
  l->len -= 1;
  return ret;
}

void* list_pop_front_generic(p_list l) {
  assert(l && l->head);
  void* ret;
  do {
    ret = l->head->key;
    p_node tmp = l->head;
    l->head = l->head->next;
    free(tmp);
  }while(0);
  
  l->len -= 1;    
  return ret;
}

static p_node _list_push_front_generic(p_list l, void* key, void *value, size_t value_len) {
  p_node n = malloc(sizeof(node));
  n->key = key;
  if(value && value_len > 0) {
    n->value = malloc(value_len);
    memcpy(n->value, value, value_len);
  }
  
  if(l->head == NULL) {
    l->head =l->tail = n;
    n->next = NULL;
  } else {
      n->next = l->head;
      l->head = n;
  }
  l->len++;
  return n;
}

p_node list_push_front_generic(p_list l, void* s) {
  assert(l != NULL && l->type == LIST_TYPE_GENERIC);
  return _list_push_front_generic(l, s, NULL, 0);
}

p_node list_push_front_string(p_list l, char* s) {
  assert(l != NULL && l->type == LIST_TYPE_STRING && s != NULL);
  return _list_push_front_generic(l, (void*)strdup(s), NULL, 0);
}

p_node list_push_front_map(p_list l, void* key, void *value, size_t value_len) {
  assert(l != NULL && ((l->type == LIST_TYPE_MAP && value != NULL) || (l->type == LIST_TYPE_SET && value == NULL)));
  return _list_push_front_generic(l, key, value, value_len);
}

p_node list_push_front_integer(p_list l, unsigned long val) {
  assert( l != NULL && l->type == LIST_TYPE_INTEGER);
  return _list_push_front_generic(l, (void*)val, NULL, 0);
}


bool list_empty(p_list l) {
  return l->len == 0;
}
void list_swap_node(p_list l, p_node n1, p_node n2) {
  assert(l && n1 &&n2);
  void * tmp_key = n1->key;
  void * tmp_value = n1->value;

  n1->key = n2->key;
  n1->value = n2->value;

  n2->key = tmp_key;
  n2->value = tmp_value;

  return;  
}

p_node list_remove_node(p_list l, p_node p, p_node n) {
  assert(l != NULL && n != NULL);

  p_node t = n->next;
  if(p != NULL)
    p->next = t;

  free(n);
  l->len--;
  return t;
}

void list_free(p_list l) {
  assert(l != NULL);
  p_node tmp = l->head;
  while(tmp != NULL) {
    p_node n = tmp->next;
    if(l->type == LIST_TYPE_STRING)
      free(tmp->key);
    else if(l->type == LIST_TYPE_MAP) {
      free(tmp->value);
    } else if(l->type == LIST_TYPE_GENERIC) {
      free(tmp->key);
    }
    free(tmp);
    tmp = n;
  }
  l->head = NULL;
  l->len = 0;
  return;
}

void list_dump(p_list l) {
  assert(l != NULL);
  p_node tmp = l->head;
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
    p_list l = list_create(LIST_TYPE_STRING);
  
    char input[] = "test this string";
    char* ptr = strtok(input, " ");
    while(ptr != NULL) {
      list_push_back_string(l, ptr);
      ptr = strtok(NULL, " ");
    }
    
    list_dump(l);
    list_free(l);
    free(l);
  }

  {
    p_list l = list_create(LIST_TYPE_INTEGER);

    list_push_back_integer(l, 1);    list_push_back_integer(l, 3);     list_push_back_integer(l, 5);
    assert(l->len == 3 && list_get_integer_value(l, 3) == 5);
    list_free(l);
    free(l);
  }

  {
    p_list l = list_create(LIST_TYPE_INTEGER);

    list_push_front_integer(l, 1);    list_push_front_integer(l, 3);     list_push_front_integer(l, 5);
    assert(l->len == 3 && list_get_integer_value(l, 3) == 1);
    list_free(l);
    free(l);
  }

  
  return;
}
