#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool check(int oldH, int newH,int other, int oldW, int newW) {
    if(newH > other)
        return other * newW > oldH *oldW;
    else
        return newH * newW > oldH * oldW;
}
int areaIter(int* height, int low, int high) {
    int area =  height[low] > height[high] ? height[high] * (high - low) : height[low] * (high - low);
    while(low < high) {
	if(height[low] >= height[high]){
	    high --;
	}
	else {
	    low ++;
	} 
    int newArea = height[low] > height[high] ? height[high] * (high - low) : height[low] * (high - low);
    if(newArea > area) area = newArea;
    } 
    return area;
}

int maxArea(int* height, int heightSize){    
    return areaIter(height, 0, heightSize - 1);
    
}
int main() {
    int input[] = {2,3,4,5,18,17,6};

    int ret = maxArea(input, sizeof(input)/sizeof(int));
    printf("%d\r\n", ret);
}
