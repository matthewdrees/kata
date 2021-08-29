// LeetCode problem 27. Remove element.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val)
    {
        const auto it = std::remove(nums.begin(), nums.end(), val);
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
        int val;
        int exp;
    };
    TestCase testCases[] = {
        { {}, 0, 0 },
        { { 1 }, 0, 1 },
        { { 1 }, 1, 0 },
        { { 1, 2 }, 1, 1 },
        { { 1, 2 }, 2, 1 },
        { { 1, 1, 2 }, 2, 2 },
        { { 1, 2, 2 }, 2, 1 },
        { { 2, 2, 3, 4 }, 3, 3 },
    };

    Solution s;
    for (auto& tc : testCases) {
        const auto ans = s.removeElement(tc.nums, tc.val);
        if (tc.exp != ans) {
            std::cout << "FAIL. prices: (nums: " << toString(tc.nums) << ", val: " << tc.val << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
