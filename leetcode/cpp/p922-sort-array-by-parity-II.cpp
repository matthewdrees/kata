// LeetCode 922. Sort array by parity II.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    std::vector<int> sortArrayByParityII(std::vector<int>& nums)
    {
        size_t j = 1;
        for (size_t i = 0; i < nums.size(); i += 2) {
            if (nums[i] % 2) {
                for (; nums[j] % 2; j += 2) { }
                std::swap(nums[i], nums[j]);
            }
        }
        return nums;
    }
};

static std::string to_string(const std::vector<int>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v) {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

int main()
{
    struct TestCase {
        std::vector<int> nums;
        std::vector<int> expected;
    };
    TestCase testCases[] = {
        { {}, {} },
        { { 1, 2 }, { 2, 1 } },
        { { 2, 1 }, { 2, 1 } },
        { { 4, 2, 5, 7 }, { 4, 5, 2, 7 } },
    };
    Solution solution;
    for (const auto& tc : testCases) {
        auto nums = tc.nums;
        const auto actual = solution.sortArrayByParityII(nums);
        if (tc.expected != actual) {
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(nums: " << to_string(tc.nums) << ")"
                      << ", expected: " << to_string(tc.expected)
                      << ", actual: " << to_string(actual)
                      << "\n";
        }
    }
    return 0;
}
