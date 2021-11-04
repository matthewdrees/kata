# LeetCode 809. Expressive words.
from typing import List


def get_letter_groups(s: str):
    lgs = []
    if len(s) == 0:
        return lgs
    prev = s[0]
    size = 1
    for i in range(1, len(s)):
        c = s[i]
        if c == prev:
            size += 1
        else:
            lgs.append((prev, size))
            prev = c
            size = 1
    lgs.append((prev, size))
    return lgs


def is_stretchy_word(lgs, word):
    word_len = len(word)
    if word_len == 0:
        return False
    i = 0
    for c1, size1 in lgs:
        j = i
        while i < word_len and c1 == word[i]:
            i += 1
        size2 = i - j
        if size1 == size2:
            continue
        if size1 >= 3 and size2 <= size1 and size2 > 0:
            continue
        return False
    return i == word_len


class Solution:
    def expressiveWords(self, s: str, words: List[str]) -> int:
        lgs = get_letter_groups(s)
        return sum(1 for word in words if is_stretchy_word(lgs, word))


if __name__ == "__main__":
    tests = (
        ("heeellooo", ["hello", "hi", "helo"], 1),
        ("heeellooo", ["heeelloooworld"], 0),
        ("zzzzzyyyyy", ["zzyy", "zy", "zyy"], 3),
        ("a", ["a", "b", ""], 1),
        ("aa", ["a", "b", ""], 0),
        ("aaa", ["a", "b", ""], 1),
        ("aaab", ["ab"], 1),
        ("aaabb", ["ab"], 0),
        ("aaabbb", ["ab"], 1),
    )
    solution = Solution()
    for s, words, exp in tests:
        act = solution.expressiveWords(s, words)
        if exp != act:
            print(f"FAIL. s: {s}, words: {words}, exp: {exp}, act: {act}")
