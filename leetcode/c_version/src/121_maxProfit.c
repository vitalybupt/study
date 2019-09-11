int maxProfit(int* prices, int pricesSize) {
    if(pricesSize <= 1) return 0;
    int minPrice = prices[0];
    int maxProfit = 0;
    for(int i = 1; i < pricesSize; ++i) {
	if(prices[i] > minPrice + maxProfit) {
	    maxProfit = (prices[i] - minPrice) > maxProfit ? prices[i] - minPrice : maxProfit;
	} else {
	    minPrice = prices[i] < minPrice ? prices[i] : minPrice;
	}
    }
    return maxProfit;
}

int main() {
    
}
