// LeetCode 560. Subarray sum equals k.
#include "leetcode.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    int subarraySum(const std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> d = { { 0, 1 } };
        int total = 0;
        int sum = 0;
        for (const auto n : nums) {
            sum += n;
            const int sum_m_k = sum - k;
            {
                auto it = d.find(sum_m_k);
                if (it != d.end()) {
                    total += it->second;
                }
            }
            auto it = d.find(sum);
            if (it != d.end()) {
                ++it->second;
            } else {
                d.insert({ sum, 1 });
            }
        }
        return total;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int k;
        int expected;
    };
    TestCase testCases[] = {
        { { 1, 1, 1 }, 2, 2 },
        { { 1, 2, 3 }, 3, 2 },
    };
    Solution solution;
    for (const auto& tc : testCases) {
        const auto actual = solution.subarraySum(tc.nums, tc.k);
        if (tc.expected != actual) {
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(nums: " << leetcode::to_string(tc.nums) << ", k: " << tc.k << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return 0;
}
