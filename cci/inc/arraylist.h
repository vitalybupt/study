#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define INIT_SIZE 20

typedef struct {
  void **val;
  int strlen;
  int size;
  int cap;
} ArrayList, *pArrayList;

pArrayList create_arraylist();
void arraylist_append_string(pArrayList a, const char* s);
void arraylist_append_generic(pArrayList a, void* s);
void* arraylist_get(pArrayList a, int i);
void free_arraylist(pArrayList a);
char* arraylist_tostring(pArrayList a);
unsigned int arraylist_get_strlen(pArrayList a);
  
void stringbuilder_test();
#endif


    
