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

static void compact_list(plist l) {
    assert(l);
    while(l->head && (unsigned long)(l->head->key) == 0) {
        list_remove_node(l, NULL, l->head);
    }
    return;
}

plist sum_list_1(plist l1, plist l2) {
  plist partial_sum = list_create(LIST_TYPE_INTEGER);
  plist carriers = list_create(LIST_TYPE_INTEGER);

  list_push_back_integer(carriers, 0);
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
    list_push_back_integer(partial_sum, s);
    list_push_back_integer(carriers, c);
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

plist sum_list_2(plist l1, plist l2) {
    plist partial_sum  = list_create(LIST_TYPE_INTEGER);
    plist carriers = list_create(LIST_TYPE_INTEGER);

    unsigned max_len = l1->len > l2->len? l1->len :l2->len;
    unsigned long s = 0; unsigned long c = 0;
    bool has_carrier = false;
        
    for(unsigned i = 1; i <= max_len; ++i) {
        unsigned l1_index = l1->len - max_len +i;
        unsigned l2_index = l2->len - max_len +i;
        if(l1_index <= 0 && l2_index > 0) {
            s = list_get_integer_value(l2, l2_index);
            c = 0;
        } else if(l1_index > 0 && l2_index <= 0)  {
            s = list_get_integer_value(l1, l1_index);
            c = 0;
        } else {
            s = (list_get_integer_value(l1, l1_index) + list_get_integer_value(l2, l2_index)) % 10;
            c = (list_get_integer_value(l1, l1_index) + list_get_integer_value(l2, l2_index)) / 10;
            if(c) has_carrier = true;
        }
        list_push_back_integer(partial_sum, s);
        list_push_back_integer(carriers, c);
    }
    if(!has_carrier) {
        list_free(carriers);
        free(carriers);
        return partial_sum;
    } else {
        compact_list(carriers);
        list_push_back_integer(carriers, 0);
        plist sum = sum_list_2(partial_sum, carriers);
        list_free(partial_sum);
        free(partial_sum);
        list_free(carriers);
        free(carriers);
        return sum;
    }
}

bool check_palindrome(plist l) {
    bool ret = true;
    
    if(l->len == 0) return ret;
    plist first_half = list_create(LIST_TYPE_INTEGER);
    pnode n = l->head;
    for( unsigned i = 0; i < l->len/2; ++i) {
        list_push_front_integer(first_half, (unsigned long)(n->key));
        n = n->next;
    }
    if(l->len%2)
        n = n->next;
    pnode m = first_half->head;
    while(n){
        if( n->key != m->key) {
            ret = false;
            break;
        }
        n = n->next;
        m = m->next;
    }
    return ret;
}

pnode check_intersection(plist l1, plist l2) {
    pnode n1 = l1->head;
    pnode n2 = l2->head;
    while(n1->next)
        n1 = n1->next;
    while(n2->next)
        n2 = n2->next;
    if(n1 != n2)
        return NULL;

    n1 = l1->head;
    n2 = l2->head;
    
    if(l1->len > l2->len) {
        for(unsigned i = 0; i < (l1->len-l2->len); ++i)
            n1 = n1->next;
    }else if(l2->len > l1->len) {
        for(unsigned i = 0; i < (l2->len-l1->len); ++i)
            n2 = n2->next;
    }

    while(n1 != n2) {
        n1 = n1->next;
        n2 = n2->next;
    }

    if(n1 == n2)
        return n1;
    else {
        /* should not happend */
        assert(NULL);
    }
}
