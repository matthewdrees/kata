// LeetCode 392. Is Subsequence.

#include <iostream>

class Solution {
public:
    bool isSubsequence(std::string s, std::string t)
    {
        if (s.empty()) {
            return true;
        }
        size_t i = 0;
        for (const char c : t) {
            if (c == s[i]) {
                ++i;
                if (i == s.size()) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    struct TestCase {
        std::string s;
        std::string t;
        bool exp;
    };

    const TestCase test_cases[] = {
        { "abc", "ahbgdc", true },
        { "axc", "ahbgdc", false },
        { "", "ahbgdc", true },
        { "a", "a", true },
        { "a", "b", false },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.isSubsequence(tc.s, tc.t);
        if (tc.exp != act) {
            std::cerr << "fail, s: " << tc.s
                      << ", t: " << tc.t
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}
