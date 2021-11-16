# LeetCode 34. Find First and last Position of Element in Sorted Array.
from typing import List
import bisect


class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        i = bisect.bisect_left(nums, target)
        if i == len(nums) or nums[i] != target:
            return [-1, -1]
        j = bisect.bisect(nums, target, i + 1)
        return [i, j - 1]


if __name__ == "__main__":
    tests = (
        ([5, 7, 7, 8, 8, 10], 4, [-1, -1]),
        ([5, 7, 7, 8, 8, 10], 5, [0, 0]),
        ([5, 7, 7, 8, 8, 10], 6, [-1, -1]),
        ([5, 7, 7, 8, 8, 10], 8, [3, 4]),
        ([5, 7, 7, 8, 8, 10], 10, [5, 5]),
        ([5, 7, 7, 8, 8, 10], 11, [-1, -1]),
        ([], 0, [-1, -1]),
        ([1, 1, 1, 1, 1, 1, 1], 1, [0, 6]),
    )
    solution = Solution()
    for nums, target, exp in tests:
        act = solution.searchRange(nums, target)
        if exp != act:
            print(f"FAIL. nums: {nums}, target: {target}, exp: {exp}, act: {act}")
