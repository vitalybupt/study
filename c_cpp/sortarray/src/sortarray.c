#include <unistd.h>
#include <stdlib.h>
#include "sortarray.h"

pArray createArray(unsigned int length) {
    pArray array = malloc(sizeof(Array));
    array->data = malloc(sizeof(pNode)*len);
    memset(array->data, 0, sizeof(pNode)*len);
    array->length = length;
    return array;
}
void setCmpAlgo(pArray array, cmpAlgo algo) {
    array->cmp = algo;
}

void addArray(pArray array, pNode target) {
    
}

