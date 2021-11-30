# LeetCode 973. K closest points to origin.
from typing import List


class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        distance_points = [[p[0] ** 2 + p[1] ** 2, p] for p in points]
        distance_points.sort(key=lambda x: x[0])
        closest = [dp[1] for dp in distance_points[:k]]
        return closest


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
