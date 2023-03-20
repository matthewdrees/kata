// LeetCode 55. Jump Game.

#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    bool canJump(const std::vector<int>& nums)
    {
        assert(nums.size() > 0);
        int carry = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (carry == 0) {
                return false;
            }
            carry = std::max(carry - 1, nums[i]);
        }
        return true;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        bool exp;
    };
    const TestCase test_cases[] = {
        { { 2, 3, 1, 1, 4 }, true },
        { { 3, 2, 1, 0, 4 }, false },
        { { 0 }, true },
        { { 1 }, true },
        { { 1, 0 }, true },
        { { 0, 1 }, false },
        { { 5, 0, 0, 0, 0, 0 }, true },
        { { 5, 0, 0, 0, 0, 0, 1 }, false },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.canJump(tc.nums);
        if (tc.exp != act) {
            std::cerr << "fail, nums: " << leetcode::to_string(tc.nums)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}