# LeetCode 289. Game of Life.
import copy
from typing import List
import pyperf
import random


class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        y_len = len(board)
        if y_len == 0:
            return
        x_len = len(board[0])
        b = copy.deepcopy(board)
        directions = (
            (-1, -1),
            (0, -1),
            (1, -1),
            (-1, 0),
            (1, 0),
            (-1, 1),
            (0, 1),
            (1, 1),
        )
        for y in range(y_len):
            for x in range(x_len):
                num_neighbors = 0
                for d in directions:
                    y_ = y + d[1]
                    if y_ >= 0 and y_ < y_len:
                        x_ = x + d[0]
                        if x_ >= 0 and x_ < x_len:
                            num_neighbors += b[y_][x_]
                if b[y][x] == 0:
                    # Dead cell, if 3 neighbors bring back to life.
                    if num_neighbors == 3:
                        board[y][x] = 1
                else:
                    # Live cell, should we kill it?
                    if num_neighbors < 2 or num_neighbors > 3:
                        board[y][x] = 0


if __name__ == "__main__":

    solution = Solution()
    tests = (
        (
            [[0, 1, 0], [0, 0, 1], [1, 1, 1], [0, 0, 0]],
            [[0, 0, 0], [1, 0, 1], [0, 1, 1], [0, 1, 0]],
        ),
        ([[1, 1], [1, 0]], [[1, 1], [1, 1]]),
        ([[1]], [[0]]),
        ([[]], [[]]),
    )

    for test in tests:
        ans = copy.deepcopy(test[0])
        exp = test[1]
        solution.gameOfLife(ans)
        if exp != ans:
            print(f"FAIL. board: {test[0]}, exp: {exp}, ans: {ans}")

    board = []
    for y in range(25):
        board.append([random.randint(0, 1) for x in range(25)])
    # print(board)
    # print("--------------------")
    # solution.gameOfLife(board)
    # print(board)
    runner = pyperf.Runner()
    runner.bench_func("f", solution.gameOfLife, board)
