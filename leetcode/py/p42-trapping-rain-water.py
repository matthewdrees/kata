# LeetCode 42. Trapping rain water.
import copy
from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        running_left_max = 0
        running_left_maxes = copy.deepcopy(height)
        for i, h in enumerate(height):
            running_left_max = max(h, running_left_max)
            running_left_maxes[i] = running_left_max
        trapped_water = 0
        running_right_max = 0
        for i in range(len(height) - 1, -1, -1):
            h = height[i]
            running_right_max = max(h, running_right_max)
            water_level = min(running_left_maxes[i], running_right_max)
            trapped_water += water_level - h
        return trapped_water


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ([], 0),
        ([0], 0),
        ([1], 0),
        ([1, 2], 0),
        ([2, 1], 0),
        ([1, 1, 1], 0),
        ([1, 2, 1], 0),
        ([2, 2, 1], 0),
        ([2, 2, 2], 0),
        ([2, 1, 2], 1),
        ([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], 6),
        ([4, 2, 0, 3, 2, 5], 9),
    )
    for test in tests:
        height = test[0]
        exp = test[1]
        ans = solution.trap(height)
        if exp != ans:
            print(f"FAIL. height: {height}, exp: {exp}, ans: {ans}")
