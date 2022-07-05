# LeetCode 1762. Buildings With an Ocean View.
from typing import List


class Solution:
    def findBuildings(self, heights: List[int]) -> List[int]:
        cur_highest = 0
        buildings_with_view = []
        for x in range(len(heights) - 1, -1, -1):
            if heights[x] > cur_highest:
                buildings_with_view.append(x)
                cur_highest = heights[x]

        buildings_with_view.reverse()
        return buildings_with_view


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], []),
        ([4, 2, 3, 1], [0, 2, 3]),
        ([4, 3, 2, 1], [0, 1, 2, 3]),
        ([1, 2, 3, 4], [3]),
    )

    for test in tests:

        heights = test[0]
        exp = test[1]
        ans = s.findBuildings(heights)
        if exp != ans:
            print(f"FAIL. heights: {heights}, exp: {exp}, ans: {ans}")
