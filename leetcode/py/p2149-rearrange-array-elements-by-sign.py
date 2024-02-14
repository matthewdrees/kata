# LeetCode 2149. Rearrange Array Elements by Sign
from typing import List


class Solution:
    def rearrangeArray(self, nums: List[int]) -> List[int]:
        ans = [0] * len(nums)
        pi = 0
        ni = 1

        for n in nums:
            if n >= 0:  # positive
                ans[pi] = n
                pi += 2
            else:  # negative
                ans[ni] = n
                ni += 2
        return ans


if __name__ == "__main__":
    test_cases = (
        ([3, 1, -2, -5, 2, -4], [3, -2, 1, -5, 2, -4]),
        ([-1, 1], [1, -1]),
    )

    solution = Solution()
    for nums, exp in test_cases:
        act = solution.rearrangeArray(nums)
        if exp != act:
            print(f"fail, nums: {nums}, exp: {exp}, act: {act}")
