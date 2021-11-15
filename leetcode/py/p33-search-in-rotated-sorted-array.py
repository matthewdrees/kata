# LeetCode 33. Search in Rotated Sorted Array.
from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        assert len(nums) > 0
        l = 0  # left index
        r = len(nums) - 1  # right index
        if nums[r] == target:
            return r
        while True:
            m = (r + l) // 2  # middle index
            if nums[m] == target:
                return m
            if l == m:
                return -1
            if nums[l] < nums[m]:
                if nums[l] <= target and target <= nums[m]:
                    r = m
                else:
                    l = m
            else:  # nums[m] < nums[r]
                if nums[m] <= target and target <= nums[r]:
                    l = m
                else:
                    r = m


if __name__ == "__main__":
    tests = (
        ([4, 5, 6, 7, 0, 1, 2], 0, 4),
        ([4, 5, 6, 7, 0, 1, 2], 1, 5),
        ([4, 5, 6, 7, 0, 1, 2], 2, 6),
        ([4, 5, 6, 7, 0, 1, 2], 3, -1),
        ([4, 5, 6, 7, 0, 1, 2], 4, 0),
        ([4, 5, 6, 7, 0, 1, 2], 5, 1),
        ([4, 5, 6, 7, 0, 1, 2], 6, 2),
        ([4, 5, 6, 7, 0, 1, 2], 7, 3),
        ([4, 5, 6, 7, 0, 1, 2], 8, -1),
        ([1], 1, 0),
        ([1], 2, -1),
        ([1, 2, 3, 4], 1, 0),
        ([1, 2, 3, 4], 2, 1),
        ([1, 2, 3, 4], 3, 2),
        ([1, 2, 3, 4], 4, 3),
        ([2, 3, 4, 1], 1, 3),
        ([2, 3, 4, 1], 2, 0),
        ([2, 3, 4, 1], 3, 1),
        ([2, 3, 4, 1], 4, 2),
        ([3, 4, 1, 2], 1, 2),
        ([3, 4, 1, 2], 2, 3),
        ([3, 4, 1, 2], 3, 0),
        ([3, 4, 1, 2], 4, 1),
    )
    solution = Solution()
    for nums, target, exp in tests:
        act = solution.search(nums, target)
        if exp != act:
            print(f"FAIL. nums: {nums}, target: {target}, exp: {exp}, act: {act}")
