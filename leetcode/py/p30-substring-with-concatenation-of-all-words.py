# LeetCode 30. Substring with Concatenation of All Words.
from typing import List
import collections


class Solution:
    def findSubstringOnOffset(
        self, offset, word_len, words_len, s, words_counter
    ) -> List[int]:
        substring_indexes = []
        cur_word_counter = collections.Counter()
        word_queue = []
        for i in range(offset, len(s) - word_len + 1, word_len):
            w = s[i : i + word_len]
            if w in words_counter:
                word_queue.append(w)
                cur_word_counter[w] += 1
                if len(word_queue) > words_len:
                    cur_word_counter[word_queue.pop(0)] -= 1
                if cur_word_counter == words_counter:
                    substring_indexes.append(i - word_len * (words_len - 1))
            else:
                word_queue.clear()
                cur_word_counter.clear()
        return substring_indexes

    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        words_counter = collections.Counter(words)
        word_len = len(words[0])
        substring_indexes = []
        for offset in range(word_len):
            substring_indexes.extend(
                self.findSubstringOnOffset(
                    offset, word_len, len(words), s, words_counter
                )
            )
        return substring_indexes


if __name__ == "__main__":
    test_cases = (
        ("abcdef", ["ab", "cd", "ef"], [0]),
        ("barfoothefoobarman", ["foo", "bar"], [0, 9]),
        ("wordgoodgoodgoodbestword", ["word", "good", "best", "word"], []),
        ("barfoofoobarthefoobarman", ["bar", "foo", "the"], [6, 9, 12]),
        ("ababababa", ["aba", "bab"], [0, 1, 2, 3]),
    )
    solution = Solution()
    for s, words, exp in test_cases:
        act = solution.findSubstring(s, words)
        act.sort()
        if exp != act:
            print(
                f"FAIL. findSubstring(s: {s}, words: {words}), exp: {exp}, act: {act}"
            )
