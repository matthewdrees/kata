# LeetCode 36. Valid Sudoku
from typing import List
import array


class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        cols = [array.array("b") for _ in range(9)]
        squares = [array.array("b") for _ in range(9)]
        for y, row in enumerate(board):
            rowa = array.array("b")
            for x, n in enumerate(row):
                if n == ".":
                    continue
                n = int(n)
                if n in rowa:
                    return False
                rowa.append(n)
                if n in cols[x]:
                    return False
                cols[x].append(n)
                sq = (y // 3) * 3 + x // 3
                if n in squares[sq]:
                    return False
                squares[sq].append(n)
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
