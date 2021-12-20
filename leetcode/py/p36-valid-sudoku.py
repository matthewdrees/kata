# LeetCode 36. Valid Sudoku
from typing import List

import pyperf


class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        col_vals = [set() for _ in range(9)]
        sq_vals = [set() for _ in range(9)]
        for y in range(9):
            row = board[y]
            row_vals = set()
            for x in range(9):
                n = row[x]
                if n == ".":
                    continue
                if n in row_vals:
                    return False
                row_vals.add(n)
                if n in col_vals[x]:
                    return False
                col_vals[x].add(n)
                sq = (y // 3) * 3 + x // 3
                if n in sq_vals[sq]:
                    return False
                sq_vals[sq].add(n)
        return True


if __name__ == "__main__":
    tests = (
        (
            [
                ["5", "3", ".", ".", "7", ".", ".", ".", "."],
                ["6", ".", ".", "1", "9", "5", ".", ".", "."],
                [".", "9", "8", ".", ".", ".", ".", "6", "."],
                ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
                ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
                ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
                [".", "6", ".", ".", ".", ".", "2", "8", "."],
                [".", ".", ".", "4", "1", "9", ".", ".", "5"],
                [".", ".", ".", ".", "8", ".", ".", "7", "9"],
            ],
            True,
        ),
        (
            [
                ["8", "3", ".", ".", "7", ".", ".", ".", "."],
                ["6", ".", ".", "1", "9", "5", ".", ".", "."],
                [".", "9", "8", ".", ".", ".", ".", "6", "."],
                ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
                ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
                ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
                [".", "6", ".", ".", ".", ".", "2", "8", "."],
                [".", ".", ".", "4", "1", "9", ".", ".", "5"],
                [".", ".", ".", ".", "8", ".", ".", "7", "9"],
            ],
            False,
        ),
    )
    solution = Solution()
    for board, exp in tests:
        act = solution.isValidSudoku(board)
        if exp != act:
            print(f"Fail. board: {board}, exp: {exp}, act: {act}")

    # board = tests[0][0]
    # runner = pyperf.Runner()
    # runner.bench_func("f", solution.isValidSudoku, board)
