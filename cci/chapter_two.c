#include <stdlib.h>
#include <assert.h>

#include "hashtable.h"
#include "chapter_two.h"


void remove_dup(plist l1, plist l2) {
  assert(l1 && l2);
  phashtable ht_set = hashtable_create();
  pnode n = l1->head;
  while(n) {
    hashtable_insert_set(ht_set, (unsigned long)n->key);
    n = n->next;
  }
  pnode prev = l2->head;
  n = prev->next;
  while(n) {
    if(hashtable_ismember_set(ht_set, (unsigned long)(n->key))){
      n = list_remove_node(l2, prev, n);
      continue;
    }
    prev = n;
    n = n->next;
  }
  hashtable_free(ht_set);
  free(ht_set);
  return;
}

pnode reverse_count(plist l, unsigned count) {
  assert(l && count < l->len);

  pnode scanner = l->head; pnode ret = NULL;
  while(count-- > 0)
    scanner = scanner->next;
  ret = l->head;

  while(scanner->next) {
    scanner = scanner->next;
    ret = ret->next;
  }

  return ret;  
}

void delete_middle_node(plist l, pnode n) {
  assert(l && n && n->next != NULL);
  pnode cur = n; pnode next = n->next;

  while(next->next != NULL) {
    cur->key = next->key;
    cur = cur->next;
    next = next->next;
  }

  cur->key = next->key;
  cur->next = NULL;
  free(next);
  l->len--;
  return;  
}

void partition_list(plist l, unsigned long pivot) {
  assert(l);

  pnode scanner = l->head;
  pnode barrier = NULL;

  while(scanner) {
    if((unsigned long)(scanner->key) < pivot) {
      if(barrier == NULL)
	barrier = l->head;
      else
	barrier = barrier->next;
      list_swap_node(l, scanner, barrier);
    }
    scanner = scanner->next;
  }
    return;
}

plist sum_list_1(plist l1, plist l2) {
  plist partial_sum = list_create(LIST_TYPE_INTEGER);
  plist carriers = list_create(LIST_TYPE_INTEGER);

  list_push_integer(carriers, 0);
  pnode n1 = l1->head;
  pnode n2 = l2->head;
  bool has_carrier = false;
  
  while(n1 || n2) {
    unsigned long s = 0;
    unsigned c = 0;
    if(n1 == NULL) {
      s = (unsigned long)(n2->key);
      c = 0;
      n2 = n2->next;
    } else if(n2 == NULL) {
      s = (unsigned long)(n1->key);
      c = 0;
      n1 = n1->next;
    } else {
      s = ((unsigned long)(n1->key) + (unsigned long)(n2->key)) % 10;
      c = ((unsigned long)(n1->key) + (unsigned long)(n2->key)) / 10;
      n1 = n1->next;
      n2 = n2->next;
    }
    list_push_integer(partial_sum, s);
    list_push_integer(carriers, c);
    if(c != 0)
      has_carrier = true;
  }

  if(!has_carrier) {
    list_free(carriers);
    free(carriers);
    return partial_sum;
  }
  else {
    plist sum = sum_list_1(partial_sum, carriers);
    list_free(carriers);
    free(carriers);
    list_free(partial_sum);
    free(partial_sum);
    return sum;
  }
}
