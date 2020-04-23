#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

phashtable hashtable_create() {
  phashtable ret = malloc(sizeof(hashtable));
  memset(ret, 0 , sizeof(hashtable));
  ret->mask = NBITS - 1;
  return ret;
}

void hashtable_insert_map(phashtable h, unsigned long key, void *value, unsigned value_len) {
  unsigned hashbucket = key*PRIME%h->mask;
  if(!h->table[hashbucket]) {
    h->table[hashbucket] = list_create(LIST_TYPE_MAP);
  }
  list_push_back_map(h->table[hashbucket], (void*)key, value, value_len);
  return;
}

void* hashtable_lookup_map(phashtable h, unsigned long key) {
  unsigned hashbucket = key*PRIME%h->mask;
  if(!h->table[hashbucket]) {
    return NULL;
  }
  
  for(p_node n = h->table[hashbucket]->head; n; n = n->next) {
    if(key == (unsigned long)(n->key)) return n->value;
  }
  return NULL;
}

void hashtable_insert_set(phashtable h, unsigned long key) {
  unsigned hashbucket = key*PRIME%h->mask;
  if(!h->table[hashbucket]) {
    h->table[hashbucket] = list_create(LIST_TYPE_SET);
  }
  list_push_back_map(h->table[hashbucket], (void*)key, NULL, 0);
  return;
}

bool hashtable_ismember_set(phashtable h, unsigned long key) {
  unsigned hashbucket = key*PRIME%h->mask;
  if(!h->table[hashbucket]) {
    return false;
  }
  for(p_node n = h->table[hashbucket]->head; n; n = n->next) {
    if(key == (unsigned long)(n->key)) return true;
  }
  return false;
}

void hashtable_free(phashtable h) {
  assert(h != NULL);
  for(unsigned i = 0; i < NBITS; ++i) {
    p_list l = h->table[i];
    if(!l) continue;
    list_free(l);
    free(l);
    l = NULL;
  }
  return;
}

void hashtable_test() {
  /* function test for map */
  phashtable ht_map = hashtable_create();
  hashtable_insert_map(ht_map, 12, "test", strlen("test") + 1);
  char* ht_val = hashtable_lookup_map(ht_map, 12);
  assert(ht_val != NULL && strncmp(ht_val, "test", strlen("test")) == 0);
  
  hashtable_insert_map(ht_map, 22, " the", strlen(" the") + 1);
  ht_val = hashtable_lookup_map(ht_map, 22);
  assert(ht_val != NULL && strncmp(ht_val, " the", strlen(" the")) == 0);
  
  hashtable_insert_map(ht_map, 1036, " hashtable", strlen(" hashtable") + 1);
  ht_val = hashtable_lookup_map(ht_map, 1036);
  assert(ht_val != NULL && strncmp(ht_val, " hashtable", strlen(" hashtable")) == 0);

  ht_val = hashtable_lookup_map(ht_map, 1082);
  assert(ht_val == NULL);
  hashtable_free(ht_map);
  free(ht_map);
  
  /* function test for set */
  phashtable ht_set = hashtable_create();
  hashtable_insert_set(ht_set, 12);
  assert(hashtable_ismember_set(ht_set, 12));
  
  hashtable_insert_set(ht_set, 22);
  assert(hashtable_ismember_set(ht_set, 22));
  
  hashtable_insert_set(ht_set, 1036);
  assert(hashtable_ismember_set(ht_set, 1036));

  assert(!hashtable_ismember_set(ht_set, 1057));

  hashtable_free(ht_set);
  free(ht_set);
  return;
}

