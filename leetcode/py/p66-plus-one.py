"""LeetCode 66. Plus One.
"""

from typing import List
import copy

class Solution:
    """dumb docstring"""
    def plus_one(self, digits : List[int]) -> List[int]:
        for x in range(len(digits) - 1, -1, -1):
            digits[x] += 1
            if digits[x] < 10:
                return digits
            else:
                digits[x] = 0
        digits.insert(0, 1)
        return digits

test_cases = (([0], [1]),
    ([9], [1,0]),
    ([8,9], [9,0]),
    ([9,9], [1, 0,0]),
    ([1,2,3], [1,2,4]),
    ([4,3,2,1], [4,3,2,2]),
)

solution = Solution()
for digits_, exp in test_cases:
    digits_copy = copy.deepcopy(digits_)
    act = solution.plus_one(digits_copy)
    if exp != act:
        print(f"digits: {digits_copy}, exp: {exp}, act: {act}")
