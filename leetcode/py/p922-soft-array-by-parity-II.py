# LeetCode 922. Sort array by parity II.
from typing import List
import copy
import pyperf


class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        len_nums = len(nums)
        if len_nums == 0:
            return nums
        even_index = 0
        odd_index = 1
        while True:
            while nums[odd_index] % 2:
                odd_index += 2
                if odd_index >= len_nums:
                    return nums
            while nums[even_index] % 2 == 0:
                even_index += 2
                if even_index >= len_nums:
                    return nums
            nums[even_index], nums[odd_index] = nums[odd_index], nums[even_index]


if __name__ == "__main__":
    solution = Solution()
    tests = (
        ([], []),
        ([1, 2], [2, 1]),
        ([2, 1], [2, 1]),
        ([4, 2, 5, 7], [4, 5, 2, 7]),
    )
    for test in tests:
        nums = copy.deepcopy(test[0])
        exp = test[1]
        ans = solution.sortArrayByParityII(nums)
        if exp != ans:
            print(f"FAIL. nums: {test[0]}, exp: {exp}, ans: {ans}")

    nums = [0] * 10000 + [1] * 10000
    runner = pyperf.Runner()
    runner.bench_func("f", solution.sortArrayByParityII, nums)
