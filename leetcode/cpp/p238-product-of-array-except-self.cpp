// LeetCode 238. Product of Array Except Self.
#include "leetcode.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> productExceptSelf(const std::vector<int>& nums)
    {
        std::vector<int> prods(nums.size(), 1);
        int mult = 1;
        std::transform(begin(nums), end(nums), begin(prods), [&](const auto n) {
            const auto mult_ = mult;
            mult = mult * n;
            return mult_;
        });
        mult = 1;
        std::transform(rbegin(nums), rend(nums), rbegin(prods), rbegin(prods), [&](const auto n, const auto p) {
            const auto mult_ = mult;
            mult = mult * n;
            return mult_ * p;
        });
        return prods;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { { 1, 2, 3, 4 }, { 24, 12, 8, 6 } },
        { { -1, 1, 0, -3, 3 }, { 0, 0, 9, 0, 0 } },
        { { 3, 7 }, { 7, 3 } },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.productExceptSelf(tc.nums);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(nums: " << leetcode::to_string(tc.nums) << ")"
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", ans: " << leetcode::to_string(ans)
                      << "\n";
        }
    }
    return 0;
}
