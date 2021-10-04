# LeetCode 415. Add Strings.

import itertools
import pyperf
import random


class Solution:
    def addStrings(self, num1: str, num2: str) -> str:
        if len(num1) <= len(num2):
            short = num1
            long = num2
        else:
            short = num2
            long = num1
        carry = 0
        l = [""] * len(long)
        s_end = -len(short) - 1
        for i in range(-1, s_end, -1):
            ans = int(short[i]) + int(long[i]) + carry
            if ans >= 10:
                carry = 1
                ans -= 10
            else:
                carry = 0
            l[i] = str(ans)
        for i in range(len(long) - len(short) - 1, -1, -1):
            if carry:
                ans = int(long[i]) + carry
                if ans >= 10:
                    carry = 1
                    ans -= 10
                else:
                    carry = 0
                l[i] = str(ans)
            else:
                l[i] = long[: i + 1]
                break
        if carry:
            l = ["1"] + l
        return "".join(l)


class Solution2:
    def addStrings(self, num1: str, num2: str) -> str:
        if len(num1) == 0:
            return num2
        if len(num2) == 0:
            return num1
        return str(int(num1) + int(num2))


class Solution3:
    def addStrings(self, num1: str, num2: str) -> str:
        output: List[str] = []
        carry: int = 0
        for n1, n2 in itertools.zip_longest(
            reversed(num1), reversed(num2), fillvalue="0"
        ):
            s = int(n1) + int(n2) + carry
            if s >= 10:
                carry = 1
                s -= 10
            else:
                carry = 0
            output.append(str(s))
        if carry:
            output.append(str(carry))
        return "".join(reversed(output))


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ("", "", ""),
        ("0", "0", "0"),
        ("0", "1", "1"),
        ("1", "0", "1"),
        ("", "0", "0"),
        ("0", "", "0"),
        ("1", "10", "11"),
        ("9", "1", "10"),
        ("1", "99", "100"),
        ("11", "123", "134"),
        ("456", "77", "533"),
    )

    for test in tests:
        num1 = test[0]
        num2 = test[1]
        exp = test[2]
        ans = solution.addStrings(num1, num2)
        if exp != ans:
            print(f"FAIL. num1: {num1}, num2: {num2}, exp: {exp}, ans: {ans}")

    num1 = "".join([str(random.randint(0, 9)) for x in range(10001)])
    num2 = "".join([str(random.randint(0, 9)) for x in range(10001)])
    # print(solution.addStrings(num1, num2))
    runner = pyperf.Runner()
    runner.bench_func("f", solution.addStrings, num1, num2)
