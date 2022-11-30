# LeetCode 45. Jump Game II.

from typing import List
import copy


class Solution:
    def jump(self, nums: List[int]) -> int:
        ans = 0
        farthest = 0
        end = 0
        for i in range(len(nums) - 1):
            f = i + nums[i]
            if farthest < f:
                farthest = f
            if farthest >= len(nums) - 1:
                ans += 1
                break
            if i == end:
                ans += 1
                end = farthest
        return ans


class Solution2:
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


test_cases = (
    ([5], 0),
    ([1, 1], 1),
    ([1, 0], 1),
    ([1, 1, 7], 2),
    ([2, 1, 7], 1),
    ([2, 3, 1], 1),
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
