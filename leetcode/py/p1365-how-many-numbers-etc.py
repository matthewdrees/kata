# LeetCode 1365. How many numbers are smaller than the current number.
import pyperf
from typing import List
import random


class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        sorted_nums = sorted(nums)
        d = {}
        last_num = float("inf")
        for x in range(len(sorted_nums)):
            if sorted_nums[x] != last_num:
                d[sorted_nums[x]] = x
            last_num = sorted_nums[x]
        output = [0] * len(nums)
        for x in range(len(nums)):
            output[x] = d[nums[x]]
        return output


# Copied from LeetCode. Indexes an array instead of using a dictionary. Smart.
class Solution2:
    def smallerNumbersThanCurrent(self, nums):
        amt_of = [0] * 102
        for n in nums:
            amt_of[n] += 1
        amt_less_than = [0] * 102
        running_less_than = 0
        for i in range(0, 101):
            running_less_than += amt_of[i]
            amt_less_than[i + 1] = running_less_than
        output = []
        for n in nums:
            output.append(amt_less_than[n])
        return output


if __name__ == "__main__":
    solution = Solution3()
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

    nums = [random.randint(0, 101) for x in range(2, 501)]
    # print(solution.smallerNumbersThanCurrent(nums))
    runner = pyperf.Runner()
    runner.bench_func("f", solution.smallerNumbersThanCurrent, nums)
