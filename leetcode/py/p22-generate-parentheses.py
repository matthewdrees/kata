# LeetCode 22. Generate parentheses.
from typing import List


def generate_parentheses_rec(l: List[str], s: List[str], left: int, right: int):
    """Backtracking recursive call to generate list of valid parentheses.

    :param l: Builds the list of strings with valid parentheses.
    :param s: The current stack of () parens.
    :param left: Number of left parens in use.
    :param right: Number of right parens in use.
    :return: None
    """
    if left > 0:
        s.append("(")
        generate_parentheses_rec(l, s, left - 1, right)
        s.pop()
    elif right == 0:
        l.append("".join(s))
        return
    if right > left:
        s.append(")")
        generate_parentheses_rec(l, s, left, right - 1)
        s.pop()


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        assert n >= 1 and n <= 8
        l = []
        generate_parentheses_rec(l, [], n, n)
        return l


if __name__ == "__main__":
    tests = (
        (1, ["()"]),
        (2, ["()()", "(())"]),
        (3, ["((()))", "(()())", "(())()", "()(())", "()()()"]),
        (
            4,
            [
                "(((())))",
                "((()()))",
                "((())())",
                "((()))()",
                "(()(()))",
                "(()()())",
                "(()())()",
                "(())(())",
                "(())()()",
                "()((()))",
                "()(()())",
                "()(())()",
                "()()(())",
                "()()()()",
            ],
        ),
    )
    solution = Solution()
    for n, exp in tests:
        exp = set(exp)
        act = set(solution.generateParenthesis(n))
        if exp != act:
            print(f"Fail. n: {n}, exp: {exp}, act: {act}")
