// LeetCode 53. Maximum subarray.
#include <iostream>
#include <vector>

class Solution {
public:
    int maxSubArray(const std::vector<int>& nums)
    {
        if (nums.empty()) {
            return 0;
        }
        int running_sum = 0;
        int largest = nums[0];
        for (const auto num : nums) {
            running_sum += num;
            if (running_sum > largest) {
                largest = running_sum;
            }
            if (running_sum < 0) {
                running_sum = 0;
            }
        }
        return largest;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int expected;
    };
    TestCase testCases[] = {
        { {}, 0 },
        { { -1 }, -1 },
        { { 1 }, 1 },
        { { 0, -1 }, 0 },
        { { -1, 0 }, 0 },
        { { -2, -1 }, -1 },
        { { -2, 1, -3, 4, -1, 2, 1, -5, 4 }, 6 },
        { { 5, 4, -1, 7, 8 }, 23 },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto actual = s.maxSubArray(tc.nums);
        if (tc.expected != actual) {
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return 0;
}
