// LeetCode 34. Find First and Last Position of Element in Sorted Array.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

#include "leetcode.hpp"

class Solution {
public:
    std::vector<int> searchRange(const std::vector<int>& nums, int target)
    {
        assert(nums.size() <= 100'000);
        std::vector<int> v = { -1, -1 };
        const auto i = std::lower_bound(nums.begin(), nums.end(), target);
        if (i == nums.end() || *i != target) {
            return v;
        }
        const auto j = std::upper_bound(i + 1, nums.end(), target);
        v[0] = static_cast<int>(std::distance(nums.begin(), i));
        v[1] = static_cast<int>(std::distance(nums.begin(), j - 1));
        return v;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int target;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { { 5, 7, 7, 8, 8, 10 }, 4, { -1, -1 } },
        { { 5, 7, 7, 8, 8, 10 }, 5, { 0, 0 } },
        { { 5, 7, 7, 8, 8, 10 }, 6, { -1, -1 } },
        { { 5, 7, 7, 8, 8, 10 }, 8, { 3, 4 } },
        { { 5, 7, 7, 8, 8, 10 }, 10, { 5, 5 } },
        { { 5, 7, 7, 8, 8, 10 }, 11, { -1, -1 } },
        { {}, 0, { -1, -1 } },
        { { 1, 1, 1, 1, 1, 1, 1 }, 1, { 0, 6 } },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.searchRange(tc.nums, tc.target);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(nums: " << leetcode::to_string(tc.nums) << ", target: " << tc.target << ")"
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", ans: " << leetcode::to_string(ans)
                      << "\n";
        }
    }
    return 0;
}