function maxProfit(prices: number[]): number {
	let m = prices[prices.length - 1];
	let z = 0;
	for(let i = prices.length - 2; i >= 0; i--) {
		z = Math.max(z, m - prices[i]);
		if (prices[i] > m) {
			m = prices[i];
		}
	}
	return z;
}
