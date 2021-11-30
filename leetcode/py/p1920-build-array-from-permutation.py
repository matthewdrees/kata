# LeetCode 1920. Build Array from Permutation.
from typing import List


class Solution:
    def buildArray(self, nums: List[int]) -> List[int]:
        return [nums[n] for n in nums]


if __name__ == "__main__":
    tests = (
        ([0, 2, 1, 5, 3, 4], [0, 1, 2, 4, 5, 3]),
        ([5, 0, 1, 2, 3, 4], [4, 5, 0, 1, 2, 3]),
    )
    solution = Solution()
    for nums, exp in tests:
        act = solution.buildArray(nums)
        if exp != act:
            print(f"Fail. nums: {nums}, exp: {exp}, act: {act}")
