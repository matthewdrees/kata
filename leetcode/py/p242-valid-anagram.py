# LeetCode 242. Valid Anagram
import collections

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        return collections.Counter(s) == collections.Counter(t)

test_cases = (
    ("anagram", "nagaram", True),
    ("rat", "car", False),
    ("a", "a", True),
    ("a", "aa", False),
    ("aa", "a", False),
)

solution = Solution()
for s, t, exp in test_cases:
    act = solution.isAnagram(s, t)
    if exp != act:
        print(f"fail, s: {s}, t: {t}, exp: {exp}, act: {act}")
