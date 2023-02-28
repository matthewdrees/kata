# LeetCode 50. Pow(x, n)


def exp_by_squaring_positive(x: float, n: int):
    """Exponent by squaring algorithm, with check for -x already done."""
    if n == 0:
        return 1.0
    if n % 2 == 0:
        return exp_by_squaring_positive(x * x, n // 2)
    return x * exp_by_squaring_positive(x * x, (n - 1) // 2)


class Solution:
    def myPow(self, x: float, n: int) -> float:
        if n == 0:
            return 1.0
        if x == 0:
            return 0.0
        if n < 0:
            x = 1 / x
            n = -n
        return exp_by_squaring_positive(x, n)


test_cases = (
    (2.0, 10, 1024.0),
    (2.1, 3, 9.261),
    (2.0, -2, 0.25),
    (0.0, -2, 0.0),
    (0.0, 2, 0.0),
    (0.0, 0, 1.0),
)

solution = Solution()
for x, n, exp in test_cases:
    act = solution.myPow(x, n)
    if exp != act:
        print(f"fail, x: {x}, n: {n}, exp: {exp}, act: {act}")
