function canJump(nums: number[]): boolean {
	let m = 0;
	for (let i = 0; i <= m && i < nums.length; i++) {
		m = Math.max(m, i + nums[i]);
	}
	return m >= nums.length - 1;
}
