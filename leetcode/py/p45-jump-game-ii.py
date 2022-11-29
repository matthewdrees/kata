# LeetCode 45. Jump Game II.

from typing import List
import copy


class Solution:
    def jump(self, nums: List[int]) -> int:
        """First take."""
        if len(nums) <= 1:
            return 0
        big_num = 10_000
        p = [big_num] * (len(nums) - 1)
        for i in range(len(p) - 1, -1, -1):
            if nums[i] == 0:
                p[i] = big_num
                continue
            j_end = i + nums[i] + 1
            if j_end > len(p):
                p[i] = 1
            else:
                p[i] = min(p[i + 1 : j_end]) + 1
        return p[0]


class Solution2:
    def jump(self, nums: List[int]) -> int:
        """Same as above, except consumes nums."""
        if len(nums) <= 1:
            return 0
        for i in range(len(nums) - 2, -1, -1):
            if nums[i] == 0:
                nums[i] = 10_000
                continue
            j_end = i + nums[i] + 1
            if j_end >= len(nums):
                nums[i] = 1
            else:
                nums[i] = min(nums[i + 1 : j_end]) + 1
        return nums[0]


class Solution3:
    def jump(self, nums: List[int]) -> int:
        """Copied from LeetCode solutions. Clever!"""
        max_i = 0
        total_j = 0
        c = 0
        for i in range(len(nums) - 1):
            if i == c:
                total_j += 1
            if max_i < (i + nums[i]):
                max_i = i + nums[i]
            if i == c:
                c = max_i
        return total_j


test_cases = (
    ([5], 0),
    ([1, 1], 1),
    ([1, 0], 1),
    ([1, 1, 7], 2),
    ([2, 1, 7], 1),
    ([2, 3, 1, 1, 4], 2),
    ([2, 3, 0, 1, 4], 2),
    ([5, 0, 0, 0, 0, 0], 1),
)
solution = Solution()
for nums, exp in test_cases:
    nums = copy.deepcopy(nums)
    act = solution.jump(nums)
    if exp != act:
        print(f"FAIL! nums: {nums}, exp: {exp}, act: {act}")
