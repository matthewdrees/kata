// LeetCode 45. Jump Game II.
#include <iostream>
#include <vector>

#include "leetcode.hpp"

class Solution {
public:
    int jump(const std::vector<int>& nums)
    {
        size_t ans = 0;
        size_t farthest = 0;
        size_t end = 0;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);
            if (farthest >= nums.size() - 1) {
                ++ans;
                break;
            }
            if (i == end) {
                ++ans;
                end = farthest;
            }
        }
        return ans;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int exp;
    };
    Solution solution;
    const TestCase test_cases[] = {
        { { 5 }, 0 },
        { { 1, 1 }, 1 },
        { { 1, 0 }, 1 },
        { { 1, 1, 7 }, 2 },
        { { 2, 1, 7 }, 1 },
        { { 2, 3, 1, 1, 4 }, 2 },
        { { 2, 3, 0, 1, 4 }, 2 },
        { { 5, 0, 0, 0, 0, 0 }, 1 },
    };
    for (const auto& tc : test_cases) {
        const auto act = solution.jump(tc.nums);
        if (tc.exp != act) {
            std::cerr << "FAIL, "
                      << "nums: " << leetcode::to_string(tc.nums)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}