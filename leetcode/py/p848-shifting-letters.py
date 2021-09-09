# LeetCode 848. Shifting letters.
from typing import List
import copy


class Solution:
    def shiftingLetters(self, s: str, shifts: List[int]) -> str:
        ret = list(s)
        carry = 0
        for x in range(len(shifts) - 1, -1, -1):
            carry = (shifts[x] + carry) % 26
            ret[x] = chr((ord(ret[x]) - 97 + carry) % 26 + 97)
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
