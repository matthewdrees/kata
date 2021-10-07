# LeetCode 1822. Sign of the product of an array.
from typing import List


class Solution:
    def arraySign(self, nums: List[int]) -> int:
        is_positive = True
        for n in nums:
            if n <= 0:
                if n == 0:
                    return 0
                else:
                    is_positive = not is_positive
        if is_positive:
            return 1
        return -1


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ([-1, -2, -3, -4, 3, 2, 1], 1),
        ([1, 5, 0, 2, -3], 0),
        ([-1, 1, -1, 1, -1], -1),
    )

    for test in tests:
        nums = test[0]
        exp = test[1]
        ans = solution.arraySign(nums)
        if exp != ans:
            print(f"FAIL. nums: {nums}, exp: {exp}, ans: {ans}")
