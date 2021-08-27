// LeetCode problem 26. Remove duplicates from sorted array.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        const auto it = std::unique(nums.begin(), nums.end());
        return static_cast<int>(std::distance(nums.begin(), it));
    }
};

static std::string toString(std::vector<int> nums)
{
    std::ostringstream oss;
    for (const auto num : nums) {
        oss << num << ',';
    }
    return oss.str();
}

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int exp;
    };
    TestCase testCases[] = {
        { {}, 0 },
        { { 1 }, 1 },
        { { 1, 2 }, 2 },
        { { 1, 1, 2 }, 2 },
        { { 1, 2, 2 }, 2 },
        { { 2, 2, 3, 4 }, 3 },
        { { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 }, 5 }
    };

    Solution s;
    for (auto& tc : testCases) {
        const auto ans = s.removeDuplicates(tc.nums);
        if (tc.exp != ans) {
            std::cout << "FAIL. prices: (nums: " << toString(tc.nums) << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
