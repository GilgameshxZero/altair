/**
 Do not return anything, modify nums in-place instead.
 */
function rotate(nums: number[], k: number): void {
	for (let i = 0; i < k; i++) {
		nums.unshift(nums.pop() ?? 0);
	}
}
