# LeetCode 205. Isomorphic Strings.


class Solution:
    def isIsomorphic2(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        d1 = {}
        d2 = {}
        for c1, c2 in zip(s, t):
            if c1 in d1:
                if c2 != d1[c1]:
                    return False
                if c1 != d2.get(c2):
                    return False
            else:
                d1[c1] = c2
                if c2 in d2:
                    return False
                d2[c2] = c1
        return True

    def isIsomorphic(self, s: str, t: str) -> bool:
        """Copied from solutions. Brilliant!"""
        return len(set(s)) == len(set(t)) == len(set(zip(s, t)))


test_cases = (
    ("", "a", False),
    ("a", "", False),
    ("", "", True),
    ("ab", "cc", False),
    ("egg", "add", True),
    ("foo", "bar", False),
    ("paper", "title", True),
    ("badc", "baba", False),
)

solution = Solution()
for s, t, exp in test_cases:
    act = solution.isIsomorphic(s, t)
    if exp != act:
        print(f"fail, s: {s}, t: {t}, exp: {exp}, act: {act}")
