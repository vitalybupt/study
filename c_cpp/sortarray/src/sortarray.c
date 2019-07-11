#include "sortarray.h"

pArray createArray(unsigned int length) {
    pArray array = malloc(sizeof(Array));
    array->data = malloc(sizeof(pNode)*length);
    memset(array->data, 0, sizeof(pNode)*length);
    array->maxLength = length;
    array->length = 0;
    return array;
}
void setCmpAlgo(pArray array, cmpAlgo algo) {
    array->cmp = algo;
}

void addArray(pArray array, pNode target) {
  int low, mid, high;
  pNode *ptr = array->data;
  mid = low = 0;
  high = array->length - 1;
  while(low <= high) {
    mid = low + (high - low )/2;
    if(array->cmp(ptr[mid], target) < 0) {
	low = mid + 1;
    } else {
	high = mid - 1;
    }
  }

  if(low == array->maxLength) {
      free(target);
      return;	  
  }

  pNode remove = array->data[array->maxLength-1];
  memmove(&(array->data[low+1]), &(array->data[low]), (array->maxLength - low - 1)*sizeof(pNode));
  array->data[low] = target;
  
  if(array->length == array->maxLength)
      free(remove);
  else
      ++array->length;
  return;
}

void emptyArray(pArray array) {
    for(int i = 0; i < array->length; ++i) {
	free(array->data[i]);
    }
    array->length = 0;
    return;
}
void deleteArray(pArray array) {
    free(array->data);
    free(array);
}

