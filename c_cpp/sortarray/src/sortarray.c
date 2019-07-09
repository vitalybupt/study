#include "sortarray.h"

pArray createArray(unsigned int length) {
    pArray array = malloc(sizeof(Array));
    array->data = malloc(sizeof(pNode)*length);
    memset(array->data, 0, sizeof(pNode)*length);
    array->maxLength = length;
    return array;
}
void setCmpAlgo(pArray array, cmpAlgo algo) {
    array->cmp = algo;
}

void addArray(pArray array, pNode target) {
  int low, mid, high;
  pNode data = array->data;
  low = 0;
  high = array->length - 1;
  while(low <= high) {
    mid = low + (high - low + 1)/2;
    if(array->cmp((data+mid), target) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  printf("find pos %d\r\n", low);
  return;
}

