# LeetCode 219. Contains Duplicate II.
from typing import List

class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        d = {}
        for i, n in enumerate(nums):
            if n in d and i - d[n] <= k:
                return True
            d[n] = i
        return False


test_cases = (
    ([1], 0, False),
    ([1,2,3,1], 3, True),
    ([1,0,1,1], 1, True),
    ([1,2,3,1,2,3], 2, False),
)

solution = Solution()
for nums, k, exp in test_cases:
    act = solution.containsNearbyDuplicate(nums, k)
    if exp != act:
        print(f"fail: nums: {nums}, k: {k}, exp: {exp}, act: {act}")
