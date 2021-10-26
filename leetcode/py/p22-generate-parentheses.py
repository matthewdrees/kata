# LeetCode 22. Generate parentheses.
from typing import List
import itertools


def is_valid_parentheses(l: List[str]) -> bool:
    """Return True if l is a list of balanced parentheses."""
    count = 0
    for c in l:
        if c == "(":
            count += 1
        else:
            count -= 1
            if count < 0:
                return False
    if count == 0:
        return True
    return False


def unique_permutations(elements):
    """Unique permutations.

    Copied from https://stackoverflow.com/questions/6284396/permutations-with-unique-values
    answer by MiniQuark.
    """
    if len(elements) == 1:
        yield (elements[0],)
    else:
        unique_elements = set(elements)
        for first_element in unique_elements:
            remaining_elements = list(elements)
            remaining_elements.remove(first_element)
            for sub_permutation in unique_permutations(remaining_elements):
                yield (first_element,) + sub_permutation


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        assert n >= 1 and n <= 8
        l = []
        for p in unique_permutations(["("] * n + [")"] * n):
            if is_valid_parentheses(p):
                l.append("".join(p))
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
    print(solution.generateParenthesis(8))
