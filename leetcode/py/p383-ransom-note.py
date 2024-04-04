# LeetCode 383. Ransom Note.
import collections


class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        counts = collections.Counter(magazine)
        for c in ransomNote:
            count = counts.get(c, 0)
            if count == 0:
                return False
            counts[c] = count - 1
        return True

    def canConstruct2(self, ransomNote: str, magazine: str) -> bool:
        magazine_counts = collections.Counter(magazine)
        ransom_counts = collections.Counter(ransomNote)
        for c, count in ransom_counts.items():
            if magazine_counts.get(c, 0) < count:
                return False
        return True


test_cases = (
    ("a", "b", False),
    ("aa", "ab", False),
    ("aa", "aab", True),
)

solution = Solution()
for ransomNote, magazine, exp in test_cases:
    act = solution.canConstruct(ransomNote, magazine)
    if exp != act:
        print(f"fail, rn: {ransomNote}, mag: {magazine}, exp: {exp}, act: {act}")
