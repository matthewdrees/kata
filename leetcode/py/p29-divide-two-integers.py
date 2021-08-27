# LeetCode Problem 29. Divide 2 integers.
from typing import List


class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        numerator = abs(dividend)
        denominator = abs(divisor)
        base2 = 0
        while base2 < 32:
            step = denominator << base2
            if step > numerator:
                break
            base2 += 1
        ans = 0
        while base2 > 0:
            base2 -= 1
            step = denominator << base2
            if numerator >= step:
                numerator -= step
                ans += 1 << base2
                if numerator == 0:
                    break
        if (dividend < 0) == (divisor < 0):  # answer is positive
            int32_max = 2147483647
            return min(ans, int32_max)
        # else answer is negative
        return -ans


if __name__ == "__main__":

    s = Solution()
    tests = (
        (10, 3, 3),
        (7, -3, -2),
        (0, 1, 0),
        (1, 1, 1),
        (100, 2, 50),
        (101, 2, 50),
        (102, 2, 51),
        (-100, 2, -50),
        (100, -2, -50),
        (100, -2, -50),
        (2147483647, 2147483647, 1),
        (-2147483648, -2147483648, 1),
        (-2147483648, 1, -2147483648),
        (-2147483648, -1, 2147483647),
        (2, 3, 0),
        (3, 3, 1),
        (5, 3, 1),
        (6, 3, 2),
        (8, 3, 2),
        (9, 3, 3),
        (11, 3, 3),
        (12, 3, 4),
        (0, 1, 0),
    )
    for dividend, divisor, exp in tests:
        ans = s.divide(dividend, divisor)
        if exp != ans:
            print(
                f"FAIL, dividend: {dividend}, divisor: {divisor}, exp: {exp}, ans: {ans}"
            )
