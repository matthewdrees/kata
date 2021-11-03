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


def is_stretchy_word(lgs1, lgs2):
    if len(lgs1) != len(lgs2):
        return False
    for lg1, lg2 in zip(lgs1, lgs2):
        if lg1[0] != lg2[0]:
            return False
        if lg1[1] == lg2[1]:
            continue
        if lg1[1] >= 3 and lg2[1] <= lg1[1]:
            continue
        return False
    return True


class Solution:
    def expressiveWords(self, s: str, words: List[str]) -> int:
        lgs1 = get_letter_groups(s)
        print(f"lgs1: {lgs1}")
        num_stretchy_words = 0
        for word in words:
            lgs2 = get_letter_groups(word)
            print(f"lgs2: {lgs2}")
            if is_stretchy_word(lgs1, lgs2):
                num_stretchy_words += 1
        return num_stretchy_words


if __name__ == "__main__":
    tests = (
        ("heeellooo", ["hello", "hi", "helo"], 1),
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
