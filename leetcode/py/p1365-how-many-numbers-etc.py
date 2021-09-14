# LeetCode 1365. How many numbers are smaller than the current number.
import pyperf
from typing import List
import random


class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        sorted_nums = sorted(nums)
        l = [0] * 101
        last_num = float("inf")
        for x in range(len(sorted_nums)):
            if sorted_nums[x] != last_num:
                l[sorted_nums[x]] = x
                last_num = sorted_nums[x]
        return [l[n] for n in nums]


if __name__ == "__main__":
    solution = Solution()
    tests = (
        ([], []),
        ([1], [0]),
        ([1, 1], [0, 0]),
        ([1, 2], [0, 1]),
        ([2, 1], [1, 0]),
        ([8, 1, 2, 2, 3], [4, 0, 1, 1, 3]),
        ([6, 5, 4, 8], [2, 1, 0, 3]),
        ([7, 7, 7, 7], [0, 0, 0, 0]),
    )
    for test in tests:
        nums = test[0]
        exp = test[1]
        ans = solution.smallerNumbersThanCurrent(nums)
        if exp != ans:
            print(f"FAIL. nums: {nums}, exp: {exp}, ans: {ans}")

    nums = [random.randint(0, 100) for x in range(2, 501)]
    # print(solution.smallerNumbersThanCurrent(nums))
    runner = pyperf.Runner()
    runner.bench_func("f", solution.smallerNumbersThanCurrent, nums)
