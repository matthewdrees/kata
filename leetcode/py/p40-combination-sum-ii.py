# LeetCode 40. Combination Sum II.

import copy
from typing import List


class Solution:
    def recurse(self, index, remainder, partials):
        if remainder < 0:
            return
        if remainder == 0:
            self.combinations.append(list(partials))
        for next_index in range(index, len(self.candidates)):
            if (
                next_index > index
                and self.candidates[next_index] == self.candidates[next_index - 1]
            ):
                continue
            n = self.candidates[next_index]
            partials.append(n)
            self.recurse(next_index + 1, remainder - n, partials)
            partials.pop()

    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        self.candidates = candidates
        self.combinations = []
        self.recurse(0, target, [])
        return self.combinations


if __name__ == "__main__":
    test_cases = (
        ([10, 1, 2, 7, 6, 1, 5], 8, [[1, 1, 6], [1, 2, 5], [1, 7], [2, 6]]),
        ([2, 5, 2, 1, 2], 5, [[1, 2, 2], [5]]),
        ([2], 1, []),
        (
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            27,
            [],
        ),
        ([2, 1, 3, 1, 4], 10, [[1, 2, 3, 4]]),
        (
            [
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
            ],
            30,
            [
                [
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                    1,
                ]
            ],
        ),
    )
    solution = Solution()
    for candidates, target, exp in test_cases:
        candidates_copy = copy.deepcopy(candidates)
        act = solution.combinationSum2(candidates_copy, target)
        act.sort()
        if exp != act:
            print(f"candidates: {candidates}, target: {target}, exp: {exp}, act: {act}")
