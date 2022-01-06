# LeetCode 947. Most Stones Removed with Same Row or Column.
from typing import List


class Solution:
    def removeStones(self, stones: List[List[int]]) -> int:
        groups = []
        for x, y in stones:
            y_ = y + 10001
            i = 0
            while i < len(groups):
                g = groups[i]
                if x in g:
                    g.add(y_)
                    break
                if y_ in g:
                    g.add(x)
                    break
                i += 1
            if i == len(groups):
                groups.append(set((x, y_)))
            else:
                for j in range(len(groups) - 1, i, -1):
                    g = groups[j]
                    if x in g or y_ in g:
                        groups[i].update(g)
                        groups.pop(j)
        return len(stones) - len(groups)


if __name__ == "__main__":

    tests = (
        ([[0, 0], [0, 1], [1, 0], [1, 2], [2, 1], [2, 2]], 5),
        ([[0, 0], [0, 2], [1, 1], [2, 0], [2, 2]], 3),
        ([[0, 0]], 0),
        ([[0, 2], [1, 0], [2, 3], [3, 1]], 0),
    )
    solution = Solution()
    for stones, exp in tests:
        ans = solution.removeStones(stones)
        if exp != ans:
            print(f"FAIL. stones: {stones}, exp: {exp}, ans: {ans}")
