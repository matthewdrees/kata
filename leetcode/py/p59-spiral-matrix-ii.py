# LeetCode 59. Spiral Matrix II.
from typing import List

class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        matrix = [[0]*n for _ in range(n)]
        num = 1
        dim0 = 0
        dim1 = n
        while dim0 < dim1:
            for x in range(dim0, dim1):
                matrix[dim0][x] = num
                num += 1
            dim1 -= 1
            for y in range(dim0 + 1, dim1):
                matrix[y][dim1] = num
                num += 1
            for x in range(dim1, dim0, -1):
                matrix[dim1][x] = num
                num += 1
            for y in range(dim1, dim0, -1):
                matrix[y][dim0] = num
                num += 1
            dim0 += 1
        return matrix

test_cases = (
    (1, [[1]]),
    (2, [[1,2], [4, 3]]),
    (3, [[1,2,3], [8, 9, 4], [7, 6, 5]]),
    (4, [[1,2,3, 4],
         [12, 13, 14, 5],
         [11, 16, 15, 6],
         [10,9, 8, 7]]),
)

solution = Solution()
for n, exp in test_cases:
    act = solution.generateMatrix(n)
    if exp != act:
        print(f"fail, n: {n}, exp: {exp}, act: {act}")
