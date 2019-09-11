#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

bool canJump(int* nums, int numsSize){
    int target = numsSize -1;
    int cur = 0;
    int range = nums[cur];
    do{

	if(cur + range >= target) return true;
	
	int next = cur;
	for(int guess = cur+1; guess <= cur+range; guess++) {
	    if(guess + nums[guess] > next + nums[next])
		next = guess;
	}
	if(next == cur) break;
	cur = next;
	range = nums[cur];
    }while(cur < target);
    return false;
    
}

int main() {
    return 0;
}
