# LeetCode 560. Subarray sum equals k.
from typing import List
import pyperf
import random


class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        """The fastest brute force solution I could come up with.

        Sadly, it wasn't fast enough. It timed out on test case #72 out of 89.
        """
        total = nums.count(k)
        len_nums = len(nums)
        i = 0
        while i < len_nums:
            local_sum = nums[i]
            j = i + 1
            while j < len_nums:
                local_sum += nums[j]
                if local_sum == k:
                    total += 1
                j += 1
            i += 1
        return total


class Solution2:
    def subarraySum(self, nums: List[int], k: int) -> int:
        """Copied this plan of attack from the Solution 4 description.

        So clever. What percentage of people would think of this solution in a
        1-2 hour time frame?
        """
        d = {0: 1}
        sum_ = 0
        count = 0
        for n in nums:
            sum_ += n
            sum_m_k = sum_ - k
            if sum_m_k in d:
                count += d[sum_m_k]
            d[sum_] = d.get(sum_, 0) + 1
        return count


if __name__ == "__main__":

    solution = Solution2()
    tests = (
        ([], 0, 0),
        ([-1], 1, 0),
        ([-1], -1, 1),
        ([1, 1], 0, 0),
        ([1, 1], 1, 2),
        ([1, 1], 2, 1),
        ([-1, 1], -1, 1),
        ([-1, 1], 0, 1),
        ([-1, 1], 1, 1),
        ([1, 1, 1], 2, 2),
        ([1, 2, 3], 3, 2),
        ([0], 0, 1),
        ([0, 0], 0, 3),
        ([0, 0, 0], 0, 6),
        ([0, 0, 0, 0], 0, 10),
        ([-5, -4, -3, -2, -1, 0, 1, 2, 3, 4], 5, 2),
        ([-5, -4, -3, -2, -1, 0, 1, 2, 3, 4], -5, 4),
        ([1, 2, 1, 2, 1], 3, 4),
    )

    for test in tests:
        nums = test[0]
        k = test[1]
        exp = test[2]
        ans = solution.subarraySum(nums, k)
        if exp != ans:
            print(f"FAIL. nums: {nums}, k: {k}, exp: {exp}, ans: {ans}")

    nums = [random.randint(-1000, 1000) for _ in range(10000)]
    k = 42
    runner = pyperf.Runner()
    runner.bench_func("f", solution.subarraySum, nums, k)
    # print(f"{solution.subarraySum(nums, k)}")
