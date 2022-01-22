# LeetCode 238. Product of Array Except Self.
from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        prods = [1] * len(nums)
        p = 1
        for i, n in enumerate(nums):
            prods[i] *= p
            p *= n
        p = 1
        for i in range(len(nums) - 1, -1, -1):
            prods[i] *= p
            p *= nums[i]
        return prods


if __name__ == "__main__":
    tests = (
        ([1, 2, 3, 4], [24, 12, 8, 6]),
        ([-1, 1, 0, -3, 3], [0, 0, 9, 0, 0]),
        ([3, 7], [7, 3]),
    )
    solution = Solution()
    for nums, exp in tests:
        act = solution.productExceptSelf(nums)
        if exp != act:
            print(f"Fail. nums: {nums}, exp: {exp}, act: {act}")
