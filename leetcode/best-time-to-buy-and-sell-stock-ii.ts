function maxProfit(prices: number[]): number {
	let z = 0;
	for (let i = 1; i < prices.length; i++) {
		if (prices[i] > prices[i - 1]) {
			z += prices[i] - prices[i - 1];
		}
	}
	return z;
}
