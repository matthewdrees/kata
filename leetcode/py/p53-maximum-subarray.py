# LeetCode 53. Maximum subarray.
from typing import List


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        largest = nums[0]
        running_sum = 0
        for num in nums:
            running_sum += num
            if running_sum > largest:
                largest = running_sum
            if running_sum < 0:
                running_sum = 0
        return largest


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ([], 0),
        ([-1], -1),
        ([1], 1),
        ([0, -1], 0),
        ([-1, 0], 0),
        ([-2, -1], -1),
        ([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6),
        ([5, 4, -1, 7, 8], 23),
    )

    for test in tests:
        nums = test[0]
        exp = test[1]
        ans = solution.maxSubArray(nums)
        if exp != ans:
            print(f"FAIL. nums: {nums}, exp: {exp}, ans: {ans}")
