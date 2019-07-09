typedef void* pNode;

typedef int (*cmpAlgo)(pNode, pNode);

typedef struct Array {
    pNode data;
    unsigned int length;
    cmpAlgo cmp;
} Array, *pArray;

pArray createArray(unsigned int len);
void setCmpAlgo(pArray, cmpAlgo);

void addArray(pArray, pNode);
