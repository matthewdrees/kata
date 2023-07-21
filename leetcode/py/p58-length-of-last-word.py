# LeetCode 58. Length of Last Word

class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        s2 = s.rstrip()
        return len(s2) - s2.rfind(' ') - 1

test_cases = (
    ("", 0),
    (" ", 0),
    ("a", 1),
    (" a", 1),
    ("Hello World", 5),
    ("   fly me   to   the moon  ", 4),
    ("luffy is still joyboy", 6)
)

solution = Solution()
for s, exp in test_cases:
    act = solution.lengthOfLastWord(s)
    if exp != act:
        print(f"fail, s: '{s}', exp: {exp}, act: {act}")