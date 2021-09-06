# LeetCode 56. Merge Intervals.
import copy
from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        if len(intervals) == 0:
            return intervals
        intervals.sort(key=lambda x: x[0])
        nlen = len(intervals)
        i = 0
        for j in range(1, nlen):
            if intervals[i][1] < intervals[j][0]:
                i += 1
                intervals[i] = intervals[j]
            elif intervals[i][1] < intervals[j][1]:
                intervals[i][1] = intervals[j][1]
        del intervals[i + 1 :]
        return intervals


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], []),
        ([[1, 1]], [[1, 1]]),
        ([[1, 2]], [[1, 2]]),
        ([[1, 2], [2, 3]], [[1, 3]]),
        ([[1, 3], [2, 3]], [[1, 3]]),
        ([[1, 4], [2, 3]], [[1, 4]]),
        ([[3, 4], [1, 2]], [[1, 2], [3, 4]]),
        ([[1, 2], [1, 3]], [[1, 3]]),
        ([[1, 2], [3, 4]], [[1, 2], [3, 4]]),
        ([[1, 2], [3, 4]], [[1, 2], [3, 4]]),
        ([[1, 3], [2, 6], [8, 10], [15, 18]], [[1, 6], [8, 10], [15, 18]]),
    )

    for test in tests:

        intervals = test[0]
        intervals_copy = copy.deepcopy(intervals)
        exp = test[1]
        ans = s.merge(intervals)
        if exp != ans:
            print(f"FAIL. s: {intervals_copy}, exp: {exp}, ans: {ans}")
