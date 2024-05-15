# LeetCode 200. Number of Islands.
from typing import List
import unittest


def fill_zero(grid: List[List[str]], x, y):
    if grid[y][x] == "0":
        return
    grid[y][x] = "0"
    if x > 0:
        fill_zero(grid, x - 1, y)
    if x + 1 < len(grid[0]):
        fill_zero(grid, x + 1, y)
    if y > 0:
        fill_zero(grid, x, y - 1)
    if y + 1 < len(grid):
        fill_zero(grid, x, y + 1)


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        num_islands = 0
        for y, row in enumerate(grid):
            for x, val in enumerate(row):
                if val == "1":
                    num_islands += 1
                    fill_zero(grid, x, y)
        return num_islands


def test_numIslands():
    test_cases = (
        (
            [
                ["1", "1", "1", "1", "0"],
                ["1", "1", "0", "1", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "0", "0", "0"],
            ],
            1,
        ),
        (
            [
                ["1", "1", "0", "0", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "1", "1"],
            ],
            3,
        ),
        (
            [
                ["1", "1", "0", "0", "0"],
                ["1", "0", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "0", "1"],
            ],
            3,
        ),
    )
    solution = Solution()
    for grid, exp in test_cases:
        act = solution.numIslands(grid)
        if exp != act:
            print(f"fail, grid: {grid}, exp: {exp}, act: {act}")


def get_random_grid(dim: int):
    import random

    random.seed(42)
    grid = []
    for _ in range(dim):
        grid.append([str(random.randint(0, 1)) for _ in range(dim)])
    return grid


def pyperf_numIslands():
    import pyperf

    runner = pyperf.Runner()
    runner.parse_args()
    solution = Solution()
    for dim in (1, 4, 8, 16, 300):
        grid = get_random_grid(dim)
        runner.bench_func(f"numIslands, dim={dim}", solution.numIslands, grid)


if __name__ == "__main__":
    test_numIslands()
    pyperf_numIslands()
