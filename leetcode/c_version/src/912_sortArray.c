#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void swap(int* nums, int n1, int n2) {
    int tmp = nums[n1];
    nums[n1] = nums[n2];
    nums[n2] = tmp;
   return;
}
int partition(int* nums, int low, int high) {
    int pivot = nums[high -1];
    int boundary = low -1;
    for(int scanner = low; scanner < high - 1; scanner++) {
	if(nums[scanner] <= pivot)
	    swap(nums, ++boundary, scanner);
    }
    swap(nums, boundary + 1, high -1);
    return boundary +1;
}

void sortArrayIter(int* nums, int low, int high) {
    if(low >= high) {return;}
    int pos = partition(nums, low, high);
    sortArrayIter(nums, low, pos - 1);
    sortArrayIter(nums, pos+1, high);
    return;
}

int* sortArray(int* nums, int numsSize, int* returnSize){
    int *input = malloc(sizeof(int)*numsSize);
    memcpy(input, nums, sizeof(int)*numsSize);
    sortArrayIter(input, 0, numsSize - 1);
    *returnSize = numsSize;
    return input;
}

int main(){
    int input[] = {5,2,3,1};
    int retSize = 0;
    int * ret = sortArray(input, 4, &retSize);
    free(ret);
    return 0;
}
