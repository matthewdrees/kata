# LeetCode 215. Kth largest element in an array.
from typing import List


class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        nums.sort()
        return nums[-k]


if __name__ == "__main__":
    tests = (
        ([3], 1, 3),
        ([3, 2, 1, 5, 6, 4], 2, 5),
        ([3, 2, 3, 1, 2, 4, 5, 5, 6], 4, 4),
    )
    solution = Solution()
    for nums, k, exp in tests:
        act = solution.findKthLargest(nums, k)
        if exp != act:
            print(f"Fail. nums: {nums}, k: {k}, exp: {exp}, act: {act}")
