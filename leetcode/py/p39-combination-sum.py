# LeetCode 39. Combination Sum.

import bisect
import copy
from typing import List


class Solution:
    def recurse(self, index, tot, partials):
        if index >= len(self.candidates):
            return
        remainder = self.target - tot
        n = self.candidates[index]
        if remainder < n:
            return
        m = remainder // n
        if remainder % n == 0:
            self.combinations.append(partials + [n] * m)

        for x in range(m, -1, -1):
            self.recurse(index + 1, tot + x * n, partials + [n] * x)

    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        self.candidates = candidates[0 : bisect.bisect(candidates, target)]
        self.target = target
        self.combinations = []
        self.recurse(0, 0, [])
        return self.combinations


if __name__ == "__main__":
    test_cases = (
        ([2, 3, 6, 7, 8], 7, [[2, 2, 3], [7]]),
        ([2, 3, 5], 8, [[2, 2, 2, 2], [2, 3, 3], [3, 5]]),
        ([2], 1, []),
    )
    solution = Solution()
    for candidates, target, exp in test_cases:
        candidates_copy = copy.deepcopy(candidates)
        act = solution.combinationSum(candidates_copy, target)
        if exp != act:
            print(f"candidates: {candidates}, target: {target}, exp: {exp}, act: {act}")
