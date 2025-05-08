# LeetCode 97. Interleaving String
import pyperf

class Solution:

    # Recursive solution with indexes. Faster than substring copies by ~30%.
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if len(s1) + len(s2) != len(s3):
            return False
        if len(s3) == 0:
            return True
        self.s1 = s1
        self.s2 = s2
        self.s3 = s3
        self.visited_arr = [[False] * (len(s2)) for _ in range(len(s1))]
        return self.isInterleaveRec(0, 0, 0)

    def isInterleaveRec(self, i1: int, i2: int, i3: int) -> bool:
        if len(self.s1) == i1:
            return self.s2[i2:] == self.s3[i3:]
        if len(self.s2) == i2:
            return self.s1[i1:] == self.s3[i3:]
        if self.visited_arr[i1-1][i2-1]:
            return False
        self.visited_arr[i1-1][i2-1] = True
        if self.s1[i1] == self.s3[i3]:
            if self.isInterleaveRec(i1+1, i2, i3+1):
                return True
        if self.s2[i2] == self.s3[i3]:
            if self.isInterleaveRec(i1, i2+1, i3+1):
                return True
        return False


class Solution2:

    # Recursive solution with substring copies.
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if len(s1) + len(s2) != len(s3):
            return False
        self.visited_arr = [[False] * (len(s2)) for _ in range(len(s1))]
        return self.isInterleaveRec(s1, s2, s3)

    def isInterleaveRec(self, s1: str, s2: str, s3: str) -> bool:
        if len(s3) == 0:
            return True
        if len(s1) == 0:
            return s2 == s3
        if len(s2) == 0:
            return s1 == s3
        if self.visited_arr[len(s1)-1][len(s2)-1]:
            return False
        self.visited_arr[len(s1)-1][len(s2)-1] = True
        if s1[0] == s3[0]:
            if self.isInterleaveRec(s1[1:], s2, s3[1:]):
                return True
        if s2[0] == s3[0]:
            if self.isInterleaveRec(s1, s2[1:], s3[1:]):
                return True
        return False

test_cases = (
    ("", "", "", True),
    ("a", "", "a", True),
    ("", "a", "a", True),
    ("a", "", "", False),
    ("", "a", "", False),
    ("", "", "a", False),
    ("a", "b", "ab", True),
    ("a", "b", "ba", True),
    ("a", "b", "aa", False),
    ("a", "b", "bb", False),
    ("aabcc", "dbbca", "aadbbcbcac", True),
    ("aabcc", "dbbca", "aadbbbaccc", False),
    ("aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaaaaaaaaaaab", False),
    ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", True),
    ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", False),
    ("bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa", "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab", "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab", False)
)

solution = Solution()

for s1, s2, s3, exp in test_cases:
    act = solution.isInterleave(s1, s2, s3)
    if exp != act:
        print(f"fail, s1: {s1}, s2: {s2}, s3: {s3}, exp: {exp}, act: {act}")

#s1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#s2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
#s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
s1 = "aabcc"
s2 = "dbbca"
s3 = "aadbbcbcac"
runner = pyperf.Runner()
runner.bench_func("isInterleave", solution.isInterleave, s1, s2, s3)
