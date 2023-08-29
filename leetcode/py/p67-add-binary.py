# LeetCode 67. Add Binary.

class Solution:
    def add_binary(self, a : str, b: str) -> str:
        return bin(int(a, 2) + int(b, 2))[2:]

class Solution2:

    def add_binary(self, a : str, b: str) -> str:
        """Lame, complicated attempt."""
        l = [int(x) for x in a]
        l.reverse()
        s = [int(x) for x in b]
        s.reverse()
        if len(a) < len(b):
            l, s = s, l
        carry = 0
        for x, s_val in enumerate(s):
            carry, l[x] = divmod(l[x] + s_val + carry, 2)
        if carry != 0:
            for x in range(len(s), len(l)):
                carry, l[x] = divmod(l[x] + carry, 2)
                if carry == 0:
                    break
            if carry != 0:
                l.append(1)
        l.reverse()
        return "".join([str(x) for x in l])

test_cases = (
    ("0", "1", "1"),
    ("1", "0", "1"),
    ("1", "1", "10"),
    ("11", "1", "100"),
    ("1", "11", "100"),
    ("1010", "1011", "10101"),
)

solution = Solution()

for a, b, exp in test_cases:
    act = solution.add_binary(a, b)
    if exp != act:
        print(f"fail. a: {a}, b: {b}, exp: {exp}, act: {act}")
