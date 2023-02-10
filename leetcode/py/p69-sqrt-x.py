# LeetCode 69. Sqrt(x).


class Solution:
    def mySqrt(self, x: int) -> int:
        # Heron's method.
        r = x
        while r * r > x:
            r = (r + x // r) // 2
        return r


test_cases = (
    (0, 0),
    (1, 1),
    (2, 1),
    (3, 1),
    (4, 2),
    (5, 2),
    (8, 2),
    (9, 3),
    (15, 3),
    (16, 4),
    (24, 4),
    (25, 5),
    (35, 5),
    (36, 6),
    (48, 6),
    (49, 7),
    (49, 7),
    (2147395599, 46339),
    (2147395600, 46340),
    (2147483647, 46340),
)

solution = Solution()
for x, exp in test_cases:
    act = solution.mySqrt(x)
    if exp != act:
        print(f"fail, x: {x}, exp: {exp}, act: {act}")
