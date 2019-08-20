#include <unistd.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int search(int* nums, int numSize, int target) {
    int index = 0;
    for(index = 0; index < numSize; index++) {
        if(nums[index] == target)
            return index;
    }
    return -1;
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int index = 0;
    for(index = 0; index < numsSize; index++) {
        if(nums[index] < target) {
            int found = search(&nums[index+1], numsSize - index - 1, target - nums[index]);
            if(found != -1 ) {
	      int *ret = malloc(sizeof(int)*2);
	      ret[0] = index;
	      ret[1] = found;
	      return ret;
            }
      }
    }
    return 0;
}
int main()
{
}
