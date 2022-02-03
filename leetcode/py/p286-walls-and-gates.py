# LeetCode 286. Walls and Gates.
import copy
from typing import List


class Solution:
    def rec(self, x, y, d):
        if x < 0 or x >= self.len_x or y < 0 or y >= self.len_y:
            return
        val = self.rooms[y][x]
        if val == -1 or val <= d:
            return
        self.rooms[y][x] = d
        self.rec(x - 1, y, d + 1)
        self.rec(x + 1, y, d + 1)
        self.rec(x, y - 1, d + 1)
        self.rec(x, y + 1, d + 1)

    def wallsAndGates(self, rooms: List[List[int]]) -> None:
        """
        Do not return anything, modify rooms in-place instead.
        """
        self.len_y = len(rooms)
        assert self.len_y > 0
        self.len_x = len(rooms[0])
        assert self.len_x > 0
        self.rooms = rooms

        for y in range(self.len_y):
            for x in range(self.len_x):
                if rooms[y][x] == 0:
                    self.rec(x - 1, y, 1)
                    self.rec(x + 1, y, 1)
                    self.rec(x, y - 1, 1)
                    self.rec(x, y + 1, 1)


tests = (
    (
        [
            [2147483647, -1, 0, 2147483647],
            [2147483647, 2147483647, 2147483647, -1],
            [2147483647, -1, 2147483647, -1],
            [0, -1, 2147483647, 2147483647],
        ],
        [[3, -1, 0, 1], [2, 2, 1, -1], [1, -1, 2, -1], [0, -1, 3, 4]],
    ),
    ([[-1]], [[-1]]),
)

solution = Solution()
for rooms, exp in tests:
    act = copy.deepcopy(exp)
    solution.wallsAndGates(act)
    if exp != act:
        print(f"Fail. rooms:\n{rooms}\nexp:{exp}\nact:\n{act}")
