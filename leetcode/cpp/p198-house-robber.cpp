// LeetCode 198. House Robber.
#include "leetcode.hpp"

#include <iostream>
#include <vector>

class Solution {
public:
    int rob(const std::vector<int>& nums)
    {
        int largep = 0;
        int large = 0;
        for (const auto n : nums) {
            const auto newlarge = std::max(n + largep, large);
            largep = large;
            large = newlarge;
        }
        return large;
    }
};

int main()
{
    struct TC {
        std::vector<int> nums;
        int exp;
    };

    const TC test_cases[] = {
        { {}, 0 },
        { { 0 }, 0 },
        { { 1 }, 1 },
        { { 1, 2, 3, 1 }, 4 },
        { { 2, 7, 9, 3, 1 }, 12 },
        { { 9, 1, 9, 1, 1 }, 19 },
        { { 9, 1, 1, 9, 1 }, 18 },
        { { 9, 1, 9, 1, 9 }, 27 }
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.rob(tc.nums);
        if (tc.exp != act) {
            std::cerr << "Fail. ( nums: " << leetcode::to_string(tc.nums)
                      << "), exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}
