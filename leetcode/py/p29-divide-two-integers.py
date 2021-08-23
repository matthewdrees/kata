# LeetCode Problem 29. Divide 2 integers.
from typing import List


class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        n = abs(dividend)
        step = abs(divisor)
        count = 1
        stepcount_stack = []
        while step <= n:
            stepcount_stack.append((step, count))
            step = step << 1
            count = count << 1
        ans = 0
        for sc in reversed(stepcount_stack):
            if n >= sc[0]:
                n -= sc[0]
                ans += sc[1]
        if (dividend < 0) == (divisor < 0):  # answer is positive
            int32_max = 2147483647
            ans = min(ans, int32_max)
        else:  # answer is negative
            ans = -ans
        return ans


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
