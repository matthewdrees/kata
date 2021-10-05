# LeetCode 680. Valid palendrome II.

import pyperf
import random
import string


class Solution:
    def validPalindrome(self, s: str) -> bool:
        def is_palendrome(i: int, j: int):
            while i < j:
                if s[i] != s[j]:
                    return False
                i += 1
                j -= 1
            return True

        i = 0
        j = len(s) - 1
        while i < j:
            if s[i] != s[j]:
                return is_palendrome(i + 1, j) or is_palendrome(i, j - 1)
            i += 1
            j -= 1
        return True


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ("a", True),
        ("ab", True),
        ("abc", False),
        ("aba", True),
        ("aba", True),
        ("bdbd", True),
        ("eedede", True),
        ("ededee", True),
        ("amanaplanacanalpanama", True),
        ("zamanaplanacanalpanama", True),
        ("amanaplanacanalpanamaz", True),
    )

    for test in tests:
        s = test[0]
        exp = test[1]
        ans = solution.validPalindrome(s)
        if exp != ans:
            print(f"FAIL. s: {s}, exp: {exp}, ans: {ans}")

    l = [random.choice(string.ascii_lowercase) for _ in range(50000)]
    l.extend(reversed(l))
    l.append("x")
    s = "".join(l)
    # print(solution.validPalindrome(s))
    runner = pyperf.Runner()
    runner.bench_func("f", solution.validPalindrome, s)
