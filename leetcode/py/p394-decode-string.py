# LeetCode 394. Decode String.
from typing import Tuple, List


def decode_rec(s: str, i: int) -> Tuple[int, List[str]]:
    l = []
    start_i = i
    len_s = len(s)
    while i < len_s:
        c = s[i]
        if c == "]":
            l.append(s[start_i:i])
            return i + 1, l
        if c.isdecimal():
            l.append(s[start_i:i])
            bracket_index = s.index("[", i + 1)
            num = int(s[i:bracket_index])
            i, l_ = decode_rec(s, bracket_index + 1)
            l.extend(l_ * num)
            start_i = i
        else:
            i += 1
    l.append(s[start_i:])
    return i, l


class Solution:
    def decodeString(self, s: str) -> str:
        _, l = decode_rec(s, 0)
        return "".join(l)


if __name__ == "__main__":
    tests = (
        ("10[a]", "aaaaaaaaaa"),
        ("2[a10[b]]", "abbbbbbbbbbabbbbbbbbbb"),
        ("z2[a10[b]]c", "zabbbbbbbbbbabbbbbbbbbbc"),
        ("3[a]2[bc]", "aaabcbc"),
        ("3[a2[c]]", "accaccacc"),
        ("2[abc]3[cd]ef", "abcabccdcdcdef"),
        ("abc3[cd]xyz", "abccdcdcdxyz"),
    )
    solution = Solution()
    for s, exp in tests:
        act = solution.decodeString(s)
        if exp != act:
            print(f"FAIL. s: {s}, exp: {exp}, act: {act}")
