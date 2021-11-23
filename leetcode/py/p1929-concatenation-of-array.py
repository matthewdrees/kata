# LeetCode 1929. Concatenation of Array.
from typing import List


class Solution:
    def getConcatenation(self, nums: List[int]) -> List[int]:
        return nums + nums


if __name__ == "__main__":
    tests = (
        ([], []),
        ([1], [1, 1]),
        ([1, 2, 1], [1, 2, 1, 1, 2, 1]),
        ([1, 3, 2, 1], [1, 3, 2, 1, 1, 3, 2, 1]),
    )
    solution = Solution()
    for nums, exp in tests:
        act = solution.getConcatenation(nums)
        if exp != act:
            print(f"FAIL. nums: {nums}, exp: {exp}, act: {act}")
