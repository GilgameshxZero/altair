function majorityElement(nums: number[]): number {
	let ci = {};
	for (let i in nums) {
		if (ci[nums[i]] === undefined) {
			ci[nums[i]] = 1;
		} else {
			ci[nums[i]]++;
		}
	}
	return Number(Object.keys(ci).reduce((a, b) => ci[a] > ci[b] ? a : b));
}
