int maxProfit(int* prices, int pricesSize) {
    if( pricesSize <= 1) return 0;
    int peak = 0; int valley = 0;
    int boundary = pricesSize -1;
    int maxProfit = 0;

    do{
	while(valley < boundary && prices[valley + 1] <= prices[valley]) valley++;
    	peak = valley + 1;
	if(peak == boundary) return maxProfit;
	while(peak < boundary && prices[peak+1] >= prices[peak]) peak++;
	maxProfit += (prices[peak] - prices[valley]);
	valley = peak +1;
    }while(valley < boundary);
    return maxProfit;
}

int main() {
    int input [] = {1,2,3,4,5};
    printf("%d\r\n", maxProfit(input, 5));
}
