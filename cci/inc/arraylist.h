#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define INIT_SIZE 20

typedef struct {
  void **val;
  int strlen;
  int size;
  int cap;
} ArrayList, *p_arraylist;

inline bool arraylist_empty(p_arraylist a) {
  return a->size == 0;
}

inline int arraylist_get_size(p_arraylist a) {
  return a->size;
}

p_arraylist arraylist_create();
void arraylist_append_string(p_arraylist a, const char* s);
void arraylist_append_generic(p_arraylist a, void* s);

void* arraylist_pop_back_generic(p_arraylist a);

void* arraylist_peak(p_arraylist a, int i);
void arraylist_free(p_arraylist a);
char* arraylist_tostring(p_arraylist a);
unsigned int arraylist_get_strlen(p_arraylist a);
  
void stringbuilder_test();
#endif


    
