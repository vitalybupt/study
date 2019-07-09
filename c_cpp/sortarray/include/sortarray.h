#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* pNode;

typedef int (*cmpAlgo)(pNode, pNode);

typedef struct Array {
    pNode *data;
    unsigned int length;
  unsigned int maxLength;
    cmpAlgo cmp;
} Array, *pArray;

pArray createArray(unsigned int len);
void setCmpAlgo(pArray, cmpAlgo);

void addArray(pArray, pNode);
