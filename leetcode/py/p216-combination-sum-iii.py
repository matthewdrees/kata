# LeetCode 216. Combination Sum III.
from typing import List


class Solution:
    def backtrack(self, num: int, nums: List[int]):
        total = sum(nums)
        count = len(nums) + 1
        if count == self.k:
            last_num = self.n - total
            if last_num >= num and last_num < 10:
                self.output.append(nums + [last_num])
            return
        if total >= self.n:
            return
        for new_num in range(num, 9):
            self.backtrack(new_num + 1, nums + [new_num])

    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        assert k >= 2 and k <= 9
        assert n >= 1 and n <= 60
        self.k = k
        self.n = n
        self.output = []
        self.backtrack(1, [])
        return self.output


def test_combinationSum3():
    test_cases = (
        (2, 1, []),
        (2, 3, [[1, 2]]),
        (2, 4, [[1, 3]]),
        (2, 10, [[1, 9], [2, 8], [3, 7], [4, 6]]),
        (2, 17, [[8, 9]]),
        (3, 7, [[1, 2, 4]]),
        (3, 9, [[1, 2, 6], [1, 3, 5], [2, 3, 4]]),
        (4, 1, []),
        (9, 45, [[1, 2, 3, 4, 5, 6, 7, 8, 9]]),
        (9, 46, []),
        (8, 36, [[1, 2, 3, 4, 5, 6, 7, 8]]),
        (8, 37, [[1, 2, 3, 4, 5, 6, 7, 9]]),
        (8, 38, [[1, 2, 3, 4, 5, 6, 8, 9]]),
    )

    solution = Solution()
    for k, n, exp in test_cases:
        act = solution.combinationSum3(k, n)
        if exp != act:
            print(f"fail, k: {k}, n: {n}, exp: {exp}, act: {act}")


test_combinationSum3()
