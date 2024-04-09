# LeetCode 128. Longest Consecutive Sequence.

from typing import List

import pyperf
import random


class Solution:
    # def longestConsecutive(self, nums: List[int]) -> int:
    #     if len(nums) == 0:
    #         return 0
    #     longest_sequence = 1
    #     s = set(nums)
    #     while s:
    #         n = s.pop()
    #         lo = n - 1
    #         while lo in s:
    #         if n - 1 not in s:
    #             x = n + 1
    #             while x in s:
    #                 x += 1
    #             cur_sequence = x - n
    #             if cur_sequence > longest_sequence:
    #                 longest_sequence = cur_sequence
    #     return longest_sequence

    def longestConsecutive2(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        longest_sequence = 1
        s = set(nums)
        for n in s:
            if n - 1 not in s:
                x = n + 1
                while x in s:
                    x += 1
                cur_sequence = x - n
                if cur_sequence > longest_sequence:
                    longest_sequence = cur_sequence
        return longest_sequence

    def longestConsecutive(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        longest_sequence = 1
        s = set(nums)
        for n in nums:
            if n - 1 not in s:
                x = n + 1
                while x in s:
                    x += 1
                cur_sequence = x - n
                if cur_sequence > longest_sequence:
                    longest_sequence = cur_sequence
        return longest_sequence


def test_longest_consecutive():
    test_cases = (
        ([100, 4, 200, 1, 3, 2], 4),
        ([0, 3, 7, 2, 5, 8, 4, 6, 0, 1], 9),
    )

    solution = Solution()
    for nums, exp in test_cases:
        act = solution.longestConsecutive(nums)
        if exp != act:
            print(f"fail. nums: {nums}, exp: {exp}, act: {act}")


def perf_longest_consecutive():
    nums = []
    random.seed(42)
    for n in range(100_000):
        nums.append(random.randint(-1_000_000_000, 1_000_000_000))
    # print(f"{nums[0:4]}")
    solution = Solution()
    runner = pyperf.Runner()
    runner.bench_func("f", solution.longestConsecutive, nums)


test_longest_consecutive()
perf_longest_consecutive()
