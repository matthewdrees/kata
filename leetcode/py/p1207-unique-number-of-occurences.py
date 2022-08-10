import collections

from typing import List


class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        d = collections.Counter()
        for n in arr:
            d[n] += 1
        return len(d) == len(set(d.values()))


solution = Solution()
tests = (
    ([1, 2, 2, 1, 1, 3], True),
    ([1, 2], False),
    ([-3, 0, 1, -3, 1, 1, 1, -3, 10, 0], True),
)
for arr, exp in tests:
    ans = solution.uniqueOccurrences(arr)
    if exp != ans:
        print(f"FAIL. arr: {arr}, exp: {exp}, ans: {ans}")
