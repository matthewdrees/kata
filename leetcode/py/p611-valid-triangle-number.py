# LeetCode problem 611. Valid Triangle Number.
import bisect
import math
from typing import List


class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        """Second take. Runtime beats 49% of other submissions.

        Added triangles rather than subtracting out non-triangles.
        """
        nums.sort()
        start = bisect.bisect_left(nums, 1)
        if len(nums) - start < 3:
            return 0
        num_triangles = 0
        for b in range(start + 1, len(nums) - 1):
            c = b + 1
            for a in range(start, b):
                a_plus_b = nums[a] + nums[b]
                c = bisect.bisect_left(nums, a_plus_b, lo=c)
                if c == len(nums):
                    num_triangles += (b - a) * (c - b - 1)
                    break
                num_triangles += c - b - 1
        return num_triangles

    def triangleNumber_take1(self, nums: List[int]) -> int:
        """First take. Runtime beats 45% of other submissions."""
        nums.sort()

        # Remove numbers < 1.
        nums = nums[bisect.bisect_left(nums, 1) :]

        # Calculate possible number of triangles.
        num_triangles = math.comb(len(nums), 3)

        # Subtract off invalid triangles
        for a in range(len(nums) - 2):
            for b in range(a + 1, len(nums) - 1):
                c = bisect.bisect_left(nums, nums[a] + nums[b], b + 1)
                if c == len(nums):
                    break
                num_triangles -= len(nums) - c
        return num_triangles


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], 0),
        ([1], 0),
        ([1, 2], 0),
        ([1, 1, 2], 0),
        ([1, 2, 0], 0),
        ([1, 2, 2], 1),
        ([1, 2, 2, 0], 1),
        ([2, 2, 3, 4], 3),
        ([4, 2, 3, 4], 4),
        ([1, 2, 4, 5, 6, 9], 5),
        ([1, 2, 3, 4, 5, 6, 7], 13),
    )
    for nums, exp in tests:
        ans = s.triangleNumber(nums)
        if exp != ans:
            print(f"FAIL, nums: {nums}, exp: {exp}, ans: {ans}")
