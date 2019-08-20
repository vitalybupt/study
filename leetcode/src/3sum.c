#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Given an array nums of n integers, are there elements a, b, c in nums */
/* such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero. */

/* Given array nums = [-1, 0, 1, 2, -1, -4], */

/* A solution set is: */
/* [ */
/*   [-1, 0, 1], */
/*   [-1, -1, 2]] */
/* ] */

int binarySearch(int* array, int low, int high, int target) {
  //  printf("binary search between low: %d high %d\r\n", low, high);
  int mid = (low + high)/2;
  if(array[mid] < target) {
    low = mid+1;
  } else {
    high = mid -1;
  }
  if(low>=high) {return low;}
  else return binarySearch(array, low, high, target);
}

void displaySums(int* nums, int size) {
  for(int i = 0; i<size; ++i) {
	printf("%d ", nums[i]);
    }
    printf("\n");      
 }

void insertSortSums(int* sortNums, int* sortNumsSize, int val) {
  int pos = binarySearch(sortNums, 0, *sortNumsSize, val);
  memmove(sortNums+pos+1, sortNums+pos, (*sortNumsSize-pos)*sizeof(int));
  sortNums[pos] = val;
  (*sortNumsSize)++;
  return;
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int factorial(int val) {
  if(val == 1) return 1;
  else return val*factorial(val-1);
}

int** threeSum(int* nums, int numsSize, int* returnSize){
  int *sortNums = malloc(sizeof(int)*numsSize);
  (*returnSize) = 0;
  memset(sortNums, 0, sizeof(int)*numsSize);
  int sortNumsSize = 0;
  int i = 0;
  while(i < numsSize) {
    //sort array so we can skip identical number to avoid duplicate
    insertSortSums(sortNums, &sortNumsSize, nums[i]);
    i++;
  }
  {
    int maxSize = factorial(sortNumsSize)/(6*factorial(sortNumsSize -3));
    int** retArrays = malloc(sizeof(int*)*maxSize);
    int** retCol = malloc(sizeof(int*));
    {
      for(int i = 0; i < sortNumsSize -2; i++) {
	for(int j = i+1; j < sortNumsSize -1; j++) {
	  for(int k = j+1; k<sortNumsSize; k++) {
	    if(sortNums[i] + sortNums[j]+sortNums[k] == 0) {
	      int* tmp = malloc(sizeof(int)*3);
	      tmp[0] = sortNums[i]; tmp[1] = sortNums[j]; tmp[2] = sortNums[k];
	      retArrays[*returnSize] = tmp;
	      (*returnSize)++;
	    }
	  }
	}
	// skip number which is identical to its previous to remove duplicate tuple
	{
	  while(sortNums[i] == sortNums[i+1]) i++;
	}
      }
    }

    return retArrays;
  }
}

void main() {
  int input[6] = {-1, 0, 1, 2, -1, -4};
  int returnsize = 0;
  threeSum(input, 6, &returnsize);
}
