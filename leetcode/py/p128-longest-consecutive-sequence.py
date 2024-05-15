# LeetCode 128. Longest Consecutive Sequence.

from typing import List

import pyperf
import random


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        longest_sequence = 1
        s = set(nums)
        for n in nums:
            if n - 1 not in s:
                hi = n + 1
                while hi in s:
                    hi += 1
                cur_sequence = hi - n
                if cur_sequence > longest_sequence:
                    longest_sequence = cur_sequence
        return longest_sequence

    def longestConsecutive_iterate_over_set(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        longest_sequence = 1
        s = set(nums)
        for n in s:
            if n - 1 not in s:
                hi = n + 1
                while hi in s:
                    hi += 1
                cur_sequence = hi - n
                if cur_sequence > longest_sequence:
                    longest_sequence = cur_sequence
        return longest_sequence

    def longestConsecutive_remove_from_set(self, nums: List[int]) -> int:
        longest_sequence = 0
        s = set(nums)
        while s:
            n = s.pop()
            lo = n - 1
            while lo in s:
                s.discard(lo)
                lo -= 1
            hi = n + 1
            while hi in s:
                s.discard(hi)
                hi += 1
            cur_sequence = hi - lo - 1
            if cur_sequence > longest_sequence:
                longest_sequence = cur_sequence
        return longest_sequence


def test_longest_consecutive():
    test_cases = (
        ([], 0),
        ([100, 4, 200, 1, 3, 2], 4),
        ([0, 3, 7, 2, 5, 8, 4, 6, 0, 1], 9),
    )

    solution = Solution()
    for nums, exp in test_cases:
        act = solution.longestConsecutive_remove_from_set(nums)
        if exp != act:
            print(f"fail. nums: {nums}, exp: {exp}, act: {act}")


def get_perftest_nums(num_elements):
    nums = []
    random.seed(42)
    for n in range(num_elements):
        nums.append(random.randint(-1_000_000_000, 1_000_000_000))
    # print(f"{nums[0:4]}")
    return nums


def perf_longest_consecutive_helper(runner, func_name, func):
    for x in (0, 1, 2, 4, 8, 16):
        num_elements = 2**x
        nums = get_perftest_nums(num_elements)
        runner.bench_func(f"{func_name}(n={num_elements})", func, nums)


def perf_longest_consecutive():
    runner = pyperf.Runner()
    runner.parse_args()
    solution = Solution()
    perf_longest_consecutive_helper(
        runner, "longestConsecutive", solution.longestConsecutive
    )
    perf_longest_consecutive_helper(
        runner,
        "longestConsecutive_iterate_over_set",
        solution.longestConsecutive_iterate_over_set,
    )
    perf_longest_consecutive_helper(
        runner,
        "longestConsecutive_remove_from_set",
        solution.longestConsecutive_remove_from_set,
    )


test_longest_consecutive()
perf_longest_consecutive()
