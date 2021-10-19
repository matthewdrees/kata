# LeetCode 1249. Minimum remove to make valid parentheses.


class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        to_remove = set()  # indexes to remove at the end
        open_indexes = []  # stack of open parentheses indexes
        for i, c in enumerate(s):
            if c == "(":
                open_indexes.append(i)
            elif c == ")":
                if len(open_indexes) == 0:
                    to_remove.add(i)
                else:
                    open_indexes.pop()
        to_remove.update(open_indexes)
        return "".join([c for i, c in enumerate(s) if i not in to_remove])


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ("", ""),
        ("a", "a"),
        ("(", ""),
        (")", ""),
        (")(", ""),
        ("))((", ""),
        ("(()", "()"),
        ("())", "()"),
        ("()(()", "()()"),
        ("())()", "()()"),
        ("lee(t(c)o)de)", "lee(t(c)o)de"),
        ("a)b(c)d", "ab(c)d"),
        ("(a(b(c)d)", "a(b(c)d)"),
    )
    for test in tests:
        s = test[0]
        exp = test[1]
        ans = solution.minRemoveToMakeValid(s)
        if exp != ans:
            print(f"FAIL. s: {s}, exp: {exp}, ans: {ans}")
