#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "chapter_ten.h"

static void merge_sort(int* pA, int* pB, int lenA, int lenB, int sizeA) {
  int i = 0; int j = 0;
  while(i < sizeA && j < lenB)  {
    if(pA[i] <= pB[j]) {
      ++i;
      lenA--;
    } else {
      memmove(&pA[i+1], &pA[i], lenA-i);
      pA[i] = pB[j];
      ++j;
      ++i;
    }
  }
  return;
}

void test_merge_sort() {
  int sortedA[10] = {2,5,9,12,15,18,24};
  int sortedB[3] = {6,11,25};
  merge_sort(sortedA, sortedB, 7, 3, 10);
  for(int i = 0; i < 10; ++i)
    printf("%d\r\n", sortedA[i]);
  return;
}
  
