# LeetCode 70. Climbing Stairs.
import math


class Solution:
    def climbStairs(self, n: int) -> int:
        if n <= 3:
            return n
        n1 = 2
        n2 = 3
        for _ in range(3, n):
            tmp = n1 + n2
            n1 = n2
            n2 = tmp
        return n2


class Solution2:
    def climbStairs(self, n: int) -> int:
        ones = n - 2
        twos = 1
        permutations = 1
        while ones >= 0:
            permutations += math.comb(ones + twos, twos)
            ones -= 2
            twos += 1
        return permutations


if __name__ == "__main__":
    tests = (
        (1, 1),
        (2, 2),
        (3, 3),
        (4, 5),
        (5, 8),
        (6, 13),
        (45, 1836311903),
    )
    solution = Solution()
    for n, exp in tests:
        act = solution.climbStairs(n)
        if exp != act:
            print(f"Fail. n: {n}, exp: {exp}, act: {act}")
