# LeetCode 973. K closest points to origin.
from typing import List


class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        points.sort(key=lambda x: x[0] * x[0] + x[1] * x[1])
        return points[:k]


if __name__ == "__main__":
    tests = (
        ([[1, 3], [-2, 2]], 1, [[-2, 2]]),
        ([[3, 3], [5, -1], [-2, 4]], 2, [[3, 3], [-2, 4]]),
    )
    solution = Solution()
    for points, k, exp in tests:
        act = solution.kClosest(points, k)
        if exp != act:
            print(f"Fail. points: {points}, k: {k}, exp: {exp}, act: {act}")
