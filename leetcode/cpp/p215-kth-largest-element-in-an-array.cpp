// LeetCode 215. Kth largest element in an array.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "leetcode.hpp"

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        assert(k >= 1 && k <= 10000);
        std::sort(begin(nums), end(nums));
        return nums.at(nums.size() - static_cast<size_t>(k));
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int k;
        int exp;
    };
    const TestCase testCases[] = {
        { { 3 }, 1, 3 },
        { { 3, 2, 1, 5, 6, 4 }, 2, 5 },
        { { 3, 2, 3, 1, 2, 4, 5, 5, 6 }, 4, 4 },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        auto nums = tc.nums;
        const auto ans = solution.findKthLargest(nums, tc.k);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(nums: " << leetcode::to_string(tc.nums) << ", k: " << tc.k << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans
                      << "\n";
        }
    }
    return 0;
}
