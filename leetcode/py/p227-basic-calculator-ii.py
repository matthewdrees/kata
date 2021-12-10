# LeetCode 227. Basic Calculator II.


class Solution:
    def calculate(self, s: str) -> int:
        last_op = "+"
        nums = []
        len_s = len(s)
        i = 0
        ops = set(("+", "-", "*", "/"))
        while i < len_s:
            if s[i].isdigit():
                n = int(s[i])
                i += 1
                while i < len_s and s[i].isdigit():
                    n = n * 10 + int(s[i])
                    i += 1
                if last_op == "+":
                    nums.append(n)
                elif last_op == "-":
                    nums.append(-n)
                elif last_op == "*":
                    nums[-1] *= n
                elif last_op == "/":
                    # Note can't use integer division (//) because negative
                    # numbers round away from zero.
                    # nums[-1] //= n
                    nums[-1] = int(nums[-1] / n)
                else:
                    assert False, f"Bad last_op: {last_op}"
            else:
                if s[i] in ops:
                    last_op = s[i]
                i += 1
        return sum(nums)


if __name__ == "__main__":
    tests = (
        ("3+2*2", 7),
        (" 3/2 ", 1),
        (" 3+5 / 2 ", 5),
        ("1", 1),
        ("42", 42),
        ("1 - 2", -1),
        ("2 * 3", 6),
        ("8/3", 2),
        ("2 + 3 * 0", 2),
        ("14 - 3/2", 13),
    )
    solution = Solution()
    for s, exp in tests:
        act = solution.calculate(s)
        if exp != act:
            print(f"FAIL. s: {s}, exp: {exp}, act: {act}")
