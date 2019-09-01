#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void display(int **arrays, int size) {
  for(int i = 0; i < size; ++i) {
    printf("[%d %d]\r\n", arrays[i][0], arrays[i][1]);
  }
  return;
}

int binarysearch(int** intervals, int low, int high, int target) {
  if(low>high) return low;
  int mid = (low+high)/2;
  if(intervals[mid][0] <= target) low = mid+1;
  else high = mid-1;
  return binarysearch(intervals, low, high, target);
}

void insertInterval(int** sortIntervals, int pos, int* sortIntervalsSize, int* interval) {
  int* tmp = malloc(sizeof(int*)*2);
  sortIntervals[pos] = tmp;
  memcpy(tmp, interval,sizeof(int)*2);
  (*sortIntervalsSize) += 1;
  return;
}

int insertSortInterval(int** sortIntervals, int* sortIntervalsSize, int* interval) {
  if((*sortIntervalsSize) == 0) {
    insertInterval(sortIntervals, 0, sortIntervalsSize, interval);
    return 0;
  }

  int pos = binarysearch(sortIntervals, 0, (*sortIntervalsSize) -1, interval[0]);

  if(pos > 0 && sortIntervals[pos-1][1] >= interval[0] ) {
    if( interval[1] > sortIntervals[pos-1][1]) {
      sortIntervals[pos-1][1] = interval[1];
    }
    return pos - 1;
  }
  memmove(sortIntervals+pos+1, sortIntervals+pos, ((*sortIntervalsSize)-pos)*sizeof(int*));
  insertInterval(sortIntervals, pos, sortIntervalsSize, interval);
  return pos;
}


int** insert(int **intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes){
  int** sortIntervals = malloc(sizeof(int*)*(intervalsSize+1));
  int sortIntervalsSize = 0;
  //sort by lower limit
  for(int i = 0; i < intervalsSize; ++i) {
    insertInterval(sortIntervals, i, &sortIntervalsSize, intervals[i]);
  }
  int pos = insertSortInterval(sortIntervals, &sortIntervalsSize, newInterval);
  
  //shrink intervals
  for(int i = pos; i < sortIntervalsSize; ++i) {
    if(sortIntervals[i][0] <= sortIntervals[i-1][1]) { // need shrink
      if(sortIntervals[i][1] > sortIntervals[i-1][1]) // need update range
	sortIntervals[i-1][1] = sortIntervals[i][1];
      int* tmp = sortIntervals[i];
      memmove(sortIntervals+i, sortIntervals+i+1, (sortIntervalsSize - i -1)*sizeof(int*));
      sortIntervalsSize -= 1;
      i -= 1;
      free(tmp);
    }
  }
  
  int* columnSizeArray = malloc(sizeof(int)*sortIntervalsSize);
  returnColumnSizes[0] = columnSizeArray;
  for(int i = 0; i< sortIntervalsSize; ++i) 
    columnSizeArray[i] = 2;
  
  (*returnSize) = sortIntervalsSize;
  return sortIntervals;
}

int main() {
  int arrays[5][2] = {{1,2}, {3,5}, {6,7}, {8,10}, {12,16}};
  int* rawarray[5] = {arrays[0], arrays[1], arrays[2], arrays[3], arrays[4]};
  int newInterval[2] = {4, 8};
  int colSize = 2;
  int returnsize = 0;
  int** colArrays = malloc(sizeof(int*));
  int** ret = insert(rawarray, 5, &colSize, newInterval, 2, &returnsize, colArrays);
  display(ret, (returnsize));
  for(int i = 0; i < returnsize; i++) {
    free(ret[i]);
  }
  free(ret);
  return 0;
}
