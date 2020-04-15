#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "arraylist.h"

pArrayList create_arraylist() {
    pArrayList a = malloc(sizeof(ArrayList));
    a->val = malloc(sizeof(char*)*INIT_SIZE);
    a->len = 0;
    a->size = 0;
    a->cap = INIT_SIZE;

    return a;
}

void append_arraylist(pArrayList a, const char* s) {
    if(a->size >= a->cap) {
        a->val = realloc(a->val, sizeof(char*)*a->cap*2);
        a->cap *= 2;
    }
    a->val[a->size] = strdup(s);
    a->len +=strlen(s);
    a->size++;
    
    return;
}

void free_arraylist(pArrayList a) {
    for(int i = 0; i < a->size; ++i) {
        free(a->val[i]);
    }
    free(a->val);
    a->val = NULL;
    a->len = 0;
    a->size = 0;
    a->cap = 0;
    return;
}

unsigned int getlen_arraylist(pArrayList a) {
    assert(a != NULL);

    return a->len;
}

char* tostring_arraylist(pArrayList a) {
    char *tmp = malloc(sizeof(char)*(a->len+1));
    memset(tmp, 0, sizeof(char)*(a->len+1));
    
    unsigned int sublen = 0;
    
    for(int i = 0; i < a->size; ++i) {
        memmove(tmp+sublen, a->val[i], strlen(a->val[i]));
        sublen += strlen(a->val[i]);
    }
    
    return tmp;
    
}
