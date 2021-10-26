// LeetCode 22. Generate parentheses.
#include "leetcode.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

bool has_valid_parens(const std::string& s)
{
    int i = 0;
    for (const char c : s) {
        if (c == '(') {
            ++i;
        } else {
            --i;
            if (i < 0) {
                return false;
            }
        }
    }
    return true;
}

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> v;
        if (n <= 0) {
            return v;
        }
        std::string s(static_cast<size_t>(n * 2), ')');
        std::fill_n(s.begin(), static_cast<size_t>(n), '(');
        if (n == 1) {
            v.push_back(s);
            return v;
        }
        do {
            if (has_valid_parens(s)) {
                v.push_back(s);
            }
        } while (std::next_permutation(s.begin() + 1, s.end() - 1));
        return v;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        int n;
        std::vector<std::string> exp;
    };
    const TestCase testCases[] = {
        { 0, {} },
        { 1, { "()" } },
        { 2, { "(())", "()()" } },
        { 3, { "((()))", "(()())", "(())()", "()(())", "()()()" } },
        { 4, { "(((())))", "((()()))", "((())())", "((()))()", "(()(()))", "(()()())", "(()())()", "(())(())", "(())()()", "()((()))", "()(()())", "()(())()", "()()(())", "()()()()" } },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.generateParenthesis(tc.n);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(n: " << tc.n << ")"
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", ans: " << leetcode::to_string(ans)
                      << "\n";
        }
    }
    return 0;
}
