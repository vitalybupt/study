#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
    int city = 0; int minimum_carry = gas[0] - cost[0]; int carry = minimum_carry;
    for(int start = 1; start < gasSize ; start ++) {
	carry += (gas[start] - cost[start]);
	if(carry < minimum_carry) {minimum_carry = carry; city = start;}
    }
    if(carry >= 0) return (city+1)%gasSize;
    else 
    return -1;
}

int main() {
    int gas[] = {5, 1, 2, 3, 4};
    int cost[] = {4, 4, 1, 5, 1};
    printf("%d\r\n", canCompleteCircuit(gas, 5, cost, 5));
    return 0;
}
