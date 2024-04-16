# LeetCode 202. Happy Number.


def sum_square_digits(n) -> int:
    total = 0
    while n != 0:
        n, m = divmod(n, 10)
        total += m**2
    return total


class Solution:
    def isHappy(self, n: int) -> bool:
        intermediate_solutions = set()
        while n != 1:
            # print(f"{n}\n")
            n = sum_square_digits(n)
            if n in intermediate_solutions:
                return False
            intermediate_solutions.add(n)
        return True


def test_sum_square_digits():

    test_cases = (
        (1, 1),
        (2, 4),
        (9, 81),
        (10, 1),
        (19, 82),
        (91, 82),
    )
    for n, exp in test_cases:
        act = sum_square_digits(n)
        if exp != act:
            print(f"fail, sum_square_digits(n: {n}), exp: {exp}, act: {act}")


def test_isHappy():
    test_cases = (
        (1, True),
        (2, False),
        (19, True),
    )
    solution = Solution()
    for n, exp in test_cases:
        act = solution.isHappy(n)
        if exp != act:
            print(f"fail, isHappy(n: {n}), exp: {exp}, act: {act}")


if __name__ == "__main__":
    test_sum_square_digits()
    test_isHappy()
