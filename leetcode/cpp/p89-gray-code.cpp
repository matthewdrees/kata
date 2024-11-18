// LeetCode 89. Gray Code.
#include "leetcode.hpp"

#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> grayCode(int n)
    {
        assert(1 <= n && n <= 16);
        std::vector<int> v;
        v.reserve(1 << n);
        v.push_back(0);
        for (int i = 0; i < n; ++i) {
            const int delta = 1 << i;
            for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
                v.push_back(*rit + delta);
            }
        }
        return v;
    }

    // Recursive solution (1st attempt).
    std::vector<int> grayCode_rec(int n)
    {
        assert(1 <= n && n <= 16);
        if (n == 1) {
            return { 0, 1 };
        }
        std::vector<int> v = grayCode(n - 1);
        v.reserve(v.size() * 2);
        const int delta = 1 << (n - 1);
        for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
            v.push_back(*rit + delta);
        }
        return v;
    }
};

int main()
{
    Solution solution;
    for (int i = 1; i < 5; ++i) {
        const auto v = solution.grayCode(i);
        std::cout << leetcode::to_string(v) << "\n";
    }
    return 0;
}
