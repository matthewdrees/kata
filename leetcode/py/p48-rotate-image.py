# LeetCode 48. Rotate Image.

import copy
from typing import List


class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        lo = 0
        hi = len(matrix) - 1
        while lo < hi:
            for i in range(hi - lo):
                tmp = matrix[lo][lo + i]
                matrix[lo][lo + i] = matrix[hi - i][lo]
                matrix[hi - i][lo] = matrix[hi][hi - i]
                matrix[hi][hi - i] = matrix[lo + i][hi]
                matrix[lo + i][hi] = tmp
            lo += 1
            hi -= 1


test_cases = (
    ([[5]], [[5]]),
    ([[1, 2], [3, 4]], [[3, 1], [4, 2]]),
    ([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [[7, 4, 1], [8, 5, 2], [9, 6, 3]]),
    (
        [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]],
        [[15, 13, 2, 5], [14, 3, 4, 1], [12, 6, 8, 9], [16, 7, 10, 11]],
    ),
    (
        [
            [1, 2, 3, 4, 5],
            [6, 7, 8, 9, 10],
            [11, 12, 13, 14, 15],
            [16, 17, 18, 19, 20],
            [21, 22, 23, 24, 25],
        ],
        [
            [21, 16, 11, 6, 1],
            [22, 17, 12, 7, 2],
            [23, 18, 13, 8, 3],
            [24, 19, 14, 9, 4],
            [25, 20, 15, 10, 5],
        ],
    ),
)

solution = Solution()

for matrix, exp in test_cases:
    act = copy.deepcopy(matrix)
    solution.rotate(act)
    if exp != act:
        print(f"FAIL, matrix: {matrix}, exp: {exp}, act: {act}")
