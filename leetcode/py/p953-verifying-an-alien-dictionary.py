# LeetCode 953. Verifying an Alien Dictionary.
from typing import List


class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        for x in range(0, len(words) - 1):
            w1 = words[x]
            w2 = words[x + 1]
            len_w1 = len(w1)
            len_w2 = len(w2)
            y = 0
            while True:
                if y < len_w1:
                    if y < len_w2:
                        if w1[y] != w2[y]:
                            if order.index(w1[y]) < order.index(w2[y]):
                                break
                            else:
                                return False
                    else:
                        return False
                else:
                    break
                y += 1
        return True


if __name__ == "__main__":
    s = Solution()
    tests = (
        (["hello", "leetcode"], "hlabcdefgijkmnopqrstuvwxyz", True),
        (["word", "world", "row"], "worldabcefghijkmnpqstuvxyz", False),
        (["apple", "app"], "abcdefghijklmnopqrstuvwxyz", False),
        (["hello", "hello"], "abcdefghijklmnopqrstuvwxyz", True),
    )
    for test in tests:
        words = test[0]
        order = test[1]
        exp = test[2]
        ans = s.isAlienSorted(words, order)
        if exp != ans:
            print(f"FAIL. words: {words}, order: {order}, exp: {exp}, ans: {ans}")
