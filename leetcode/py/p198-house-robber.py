# LeetCode 198. House Robber.

from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        largep = 0
        large = 0
        for n in nums:
            newlarge = max(n + largep, large)
            largep = large
            large = newlarge
        return large

test_cases = (
    ([], 0),
    ([0], 0),
    ([1], 1),
    ([1,2,3,1], 4),
    ([2, 7, 9, 3, 1], 12),
    ([9, 1, 1, 9, 1], 18),
    ([9, 1, 9, 3, 9], 27),
    )

solution = Solution()

for nums, exp in test_cases:
    act = solution.rob(nums)
    if exp != act:
        print(f"fail, nums: {nums}, exp: {exp}, act: {act}")
