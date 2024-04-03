# LeetCode 392. Is Subsequence.


class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        if len(s) == 0:
            return True
        i = 0
        for c in t:
            if c == s[i]:
                i += 1
                if i == len(s):
                    return True
        return False


test_cases = (
    ("abc", "ahbgdc", True),
    ("axc", "ahbgdc", False),
    ("", "", True),
    ("a", "a", True),
    ("a", "b", False),
)

solution = Solution()
for s, t, exp in test_cases:
    act = solution.isSubsequence(s, t)
    if exp != act:
        print(f"Fail. s: {s}, t: {t}, exp: {exp}, act: {act}")
