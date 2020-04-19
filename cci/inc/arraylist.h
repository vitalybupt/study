#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define INIT_SIZE 20

typedef struct {
    char **val;
    unsigned int len;
    unsigned int size;
    unsigned int cap;
} ArrayList, *pArrayList;

pArrayList create_arraylist();
void append_arraylist(pArrayList a, const char* s);
void free_arraylist(pArrayList a);
char* tostring_arraylist(pArrayList a);
unsigned int getlen_arraylist(pArrayList a);

void stringbuilder_test();
#endif


    
