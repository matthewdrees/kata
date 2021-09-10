# LeetCode 848. Shifting letters.
from typing import List
import pyperf
import string


class Solution:
    def shiftingLetters(self, s: str, shifts: List[int]) -> str:
        ret = list(s)
        carry = 0
        for x in range(len(shifts) - 1, -1, -1):
            carry = (shifts[x] + carry) % 26
            ret[x] = string.ascii_lowercase[(ord(ret[x]) - 97 + carry) % 26]
        return "".join(ret)


if __name__ == "__main__":
    solution = Solution()
    tests = (
        ("", [], ""),
        ("a", [1], "b"),
        ("t", [1], "u"),
        ("z", [1], "a"),
        ("abc", [3, 5, 9], "rpl"),
        ("aaa", [1, 2, 3], "gfd"),
    )
    for test in tests:
        s = test[0]
        shifts = test[1]
        exp = test[2]
        ans = solution.shiftingLetters(s, shifts)
        if exp != ans:
            print(f"FAIL. s: {s}, shifts: {shifts}, exp: {exp}, ans: {ans}")

    s = "a" * 10000
    shifts = [179424691] * 10000
    runner = pyperf.Runner()
    runner.bench_func("f", solution.shiftingLetters, s, shifts)
