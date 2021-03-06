#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdbool.h>

#include "list.h"

#define NBITS 1024
#define PRIME 73

typedef struct {
  p_list table[NBITS];
  unsigned mask;
  int number;
} hashtable, *phashtable;

phashtable hashtable_create();
void hashtable_insert_map(phashtable h, unsigned long key, void *value, unsigned value_len);
void* hashtable_lookup_map(phashtable h, unsigned long key);
void hashtable_insert_set(phashtable h, unsigned long key);
bool hashtable_ismember_set(phashtable h, unsigned long key);
void hashtable_remove_set(phashtable h, unsigned long key);
bool hashtable_empty(phashtable h);
void hashtable_free(phashtable h);
void hashtable_test();
#endif
