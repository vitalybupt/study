int jump(int* nums, int numsSize){
    if(numsSize == 1) return 0;
    int target = numsSize -1;
    int steps = 0;
    int cur = 0;
    int range = nums[0];
    do{
	if(cur + range >= target) return steps + 1;
	int next = cur;
	for(int guess = cur+1; guess <= cur+range; guess++) {
	    if(guess + nums[guess] > next + nums[next])
		next = guess;
	}
	if(next == cur) break;
	cur = next;
	range = nums[cur];
	steps++;
    }while(cur < target);
    return -1;
}

int main() {
    
}
