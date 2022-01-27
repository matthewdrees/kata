# LeetCode 37. Sudoku solver.
import copy
from typing import List


def get_square_from_x_y(x, y):
    return (y // 3) * 3 + x // 3


class Solution:
    def __init__(self):
        # List of 9 sets for numbers in a given row, column, or square.
        self.row_nums = []
        self.col_nums = []
        self.sq_nums = []

        # List of empty
        self.empty_cells = []

    def solve_it(self, empty_cells_index):

        if empty_cells_index >= len(self.empty_cells):
            return True

        x, y, _ = self.empty_cells[empty_cells_index]
        sq = get_square_from_x_y(x, y)
        for n in range(1, 10):
            if n in self.row_nums[y] or n in self.col_nums[x] or n in self.sq_nums[sq]:
                continue
            # We've got a candidate!
            self.empty_cells[empty_cells_index][2] = n
            self.row_nums[y].add(n)
            self.col_nums[x].add(n)
            self.sq_nums[sq].add(n)
            if self.solve_it(empty_cells_index + 1):
                return True
            self.row_nums[y].remove(n)
            self.col_nums[x].remove(n)
            self.sq_nums[sq].remove(n)

        return False

    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        self.row_nums = [set() for _ in range(9)]
        self.col_nums = [set() for _ in range(9)]
        self.sq_nums = [set() for _ in range(9)]
        self.empty_cells = []

        for y in range(len(board)):
            for x in range(len(board[y])):
                if board[y][x] == ".":
                    self.empty_cells.append([x, y, 0])
                else:
                    n = int(board[y][x])
                    self.row_nums[y].add(n)
                    self.col_nums[x].add(n)
                    self.sq_nums[get_square_from_x_y(x, y)].add(n)

        if self.solve_it(0):
            for x, y, val in self.empty_cells:
                board[y][x] = str(val)


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
            [
                ["5", "3", "4", "6", "7", "8", "9", "1", "2"],
                ["6", "7", "2", "1", "9", "5", "3", "4", "8"],
                ["1", "9", "8", "3", "4", "2", "5", "6", "7"],
                ["8", "5", "9", "7", "6", "1", "4", "2", "3"],
                ["4", "2", "6", "8", "5", "3", "7", "9", "1"],
                ["7", "1", "3", "9", "2", "4", "8", "5", "6"],
                ["9", "6", "1", "5", "3", "7", "2", "8", "4"],
                ["2", "8", "7", "4", "1", "9", "6", "3", "5"],
                ["3", "4", "5", "2", "8", "6", "1", "7", "9"],
            ],
        ),
        (
            [
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
                [".", ".", ".", ".", ".", ".", ".", ".", "."],
            ],
            [
                ["1", "2", "3", "4", "5", "6", "7", "8", "9"],
                ["4", "5", "6", "7", "8", "9", "1", "2", "3"],
                ["7", "8", "9", "1", "2", "3", "4", "5", "6"],
                ["2", "1", "4", "3", "6", "5", "8", "9", "7"],
                ["3", "6", "5", "8", "9", "7", "2", "1", "4"],
                ["8", "9", "7", "2", "1", "4", "3", "6", "5"],
                ["5", "3", "1", "6", "4", "2", "9", "7", "8"],
                ["6", "4", "2", "9", "7", "8", "5", "3", "1"],
                ["9", "7", "8", "5", "3", "1", "6", "4", "2"],
            ],
        ),
    )
    solution = Solution()
    for board, exp in tests:
        act = copy.deepcopy(board)
        solution.solveSudoku(act)
        if exp != act:
            print(f"Fail. board:\n {board}\n, exp: \n{exp}\n, act: \n{act}")
