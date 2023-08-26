// LeetCode 66. Plus One.

#include "leetcode.hpp"

#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits)
    {
        for (auto d = digits.rbegin(); d != digits.rend(); ++d) {
            ++(*d);
            if (*d < 10) {
                return digits;
            } else {
                *d = 0;
            }
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> digits;
        std::vector<int> exp;
    };

    TestCase test_cases[] = {
        { { 0 }, { 1 } },
        { { 9 }, { 1, 0 } },
        { { 8, 9 }, { 9, 0 } },
        { { 9, 8 }, { 9, 9 } },
        { { 9, 9 }, { 1, 0, 0 } },
        { { 1, 2, 3 }, { 1, 2, 4 } },
        { { 4, 3, 2, 1 }, { 4, 3, 2, 2 } },
    };
    Solution solution;
    for (auto& tc : test_cases) {
        auto digits_copy = tc.digits;
        auto act = solution.plusOne(digits_copy);
        if (tc.exp != act) {
            std::cerr << "fail, digits: " << leetcode::to_string(tc.digits)
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
}