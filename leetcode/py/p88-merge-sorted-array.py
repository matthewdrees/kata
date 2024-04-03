# LeetCode 88. Merge Sorted Array.
from typing import List
import copy


class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        i1 = m - 1
        i2 = len(nums2) - 1
        for x in range(len(nums1) - 1, -1, -1):
            if i1 < 0:
                nums1[: x + 1] = nums2[: i2 + 1]
                return
            elif i2 < 0:
                return
            elif nums1[i1] < nums2[i2]:
                nums1[x] = nums2[i2]
                i2 -= 1
            else:
                nums1[x] = nums1[i1]
                i1 -= 1


test_cases = (
    ([1, 2, 3, 0, 0, 0], 3, [2, 5, 6], [1, 2, 2, 3, 5, 6]),
    ([4, 5, 6, 0, 0, 0], 3, [1, 2, 3], [1, 2, 3, 4, 5, 6]),
    ([], 0, [], []),
    ([1], 1, [], [1]),
    ([0], 1, [1], [1]),
    ([1, 0], 1, [1], [1, 1]),
)

solution = Solution()
for nums1, m, nums2, exp in test_cases:
    n = len(nums2)
    act = copy.deepcopy(nums1)
    solution.merge(act, m, nums2, n)
    if exp != act:
        print(
            f"fail, nums1: {nums1}, m: {m}, nums2: {nums2}, n: {n}, exp: {exp}, act: {act}"
        )
