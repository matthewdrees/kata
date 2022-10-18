# LeetCode 30. Substring with Concatenation of All Words.
from typing import List
import collections


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        word_counter = collections.Counter()
        word_counter.update(words)
        d = collections.OrderedDict()
        word_len = len(words[0])
        for i in range(0, len(s) - word_len + 1):
            w = s[i : i + word_len]
            if w in word_counter:
                d[i] = w
        substring_indexes = []
        while d:
            cur_word_counter = collections.Counter()
            i = next(iter(d))
            word_queue = []
            keys_to_remove = [i]
            while True:
                w = d[i]
                word_queue.append(w)
                cur_word_counter[w] += 1
                if len(word_queue) > len(words):
                    cur_word_counter[word_queue.pop(0)] -= 1
                if cur_word_counter == word_counter:
                    substring_indexes.append(i - word_len * (len(words) - 1))
                i += word_len
                if i not in d:
                    break
                keys_to_remove.append(i)
            for key in keys_to_remove:
                del d[key]
        substring_indexes.sort()
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
        if exp != act:
            print(
                f"FAIL. findSubstring(s: {s}, words: {words}), exp: {exp}, act: {act}"
            )
