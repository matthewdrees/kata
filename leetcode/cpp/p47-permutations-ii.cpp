// LeetCode 47. Permutations II.
#include "leetcode.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums)
    {
        if (nums.empty()) {
            return {};
        }
        if (nums.size() == 1) {
            return { nums };
        }
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> permutations = { nums };
        if (nums.size() == 2) {
            if (nums[0] != nums[1]) {
                permutations.push_back({ nums[1], nums[0] });
            }
            return permutations;
        }
        while (true) {
            // Half of all permutations are swapping the last 2 elements.
            // Optimize that case.
            const size_t i1 = nums.size() - 1;
            const size_t i2 = nums.size() - 2;
            if (nums[i2] < nums[i1]) {
                std::swap(nums[i1], nums[i2]);
                permutations.push_back(nums);
            }

            // Optimize last 3 elements.
            const size_t i3 = nums.size() - 3;
            if (nums[i3] < nums[i2]) {
                const int tmp = nums[i1];
                if (nums[i3] < nums[i1]) {
                    // Rotate right
                    nums[i1] = nums[i2];
                    nums[i2] = nums[i3];
                    nums[i3] = tmp;
                } else {
                    // Rotate left
                    nums[i1] = nums[i3];
                    nums[i3] = nums[i2];
                    nums[i2] = tmp;
                }
                permutations.push_back(nums);
                continue;
            }

            bool do_continue = false;
            for (size_t i = nums.size() - 3; i-- > 0;) {
                const auto n1 = nums[i];
                const auto n2 = nums[i + 1];
                if (n1 < n2) {
                    auto j = nums.size();
                    while (j-- > i + 1 && n1 >= nums[j]) {
                        // burn through loop
                    }
                    std::swap(nums[i], nums[j]);
                    std::reverse(nums.begin() + i + 1, nums.end());
                    permutations.push_back(nums);
                    do_continue = true;
                    break;
                }
            }
            if (do_continue) {
                continue;
            }
            break;
        }
        return permutations;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        std::vector<std::vector<int>> exp;
    };
    const TestCase testCases[] = {
        { {}, {} },
        { { 7 }, { { 7 } } },
        { { 0, 1 },
            { { 0, 1 }, { 1, 0 } } },
        { { 1, 0 },
            { { 0, 1 }, { 1, 0 } } },
        { { 1, 1, 2 },
            { { 1, 1, 2 }, { 1, 2, 1 }, { 2, 1, 1 } } },
        { { 1, 2, 3 },
            { { 1, 2, 3 }, { 1, 3, 2 }, { 2, 1, 3 }, { 2, 3, 1 }, { 3, 1, 2 }, { 3, 2, 1 } } },
        { { 1, 1, 2, 2 },
            { { 1, 1, 2, 2 }, { 1, 2, 1, 2 }, { 1, 2, 2, 1 }, { 2, 1, 1, 2 }, { 2, 1, 2, 1 }, { 2, 2, 1, 1 } } },
        { { 1, 1, 2, 3 },
            { { 1, 1, 2, 3 }, { 1, 1, 3, 2 }, { 1, 2, 1, 3 }, { 1, 2, 3, 1 }, { 1, 3, 1, 2 }, { 1, 3, 2, 1 },
                { 2, 1, 1, 3 }, { 2, 1, 3, 1 }, { 2, 3, 1, 1 }, { 3, 1, 1, 2 }, { 3, 1, 2, 1 }, { 3, 2, 1, 1 } } },
        { { 1, 3, 2, 3 },
            { { 1, 2, 3, 3 }, { 1, 3, 2, 3 }, { 1, 3, 3, 2 }, { 2, 1, 3, 3 }, { 2, 3, 1, 3 }, { 2, 3, 3, 1 },
                { 3, 1, 2, 3 }, { 3, 1, 3, 2 }, { 3, 2, 1, 3 }, { 3, 2, 3, 1 }, { 3, 3, 1, 2 }, { 3, 3, 2, 1 } } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        auto copy = tc.nums;
        const auto ans = s.permuteUnique(copy);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(nums: " << leetcode::to_string(tc.nums) << ")"
                      << "\n, exp: " << leetcode::to_string(tc.exp)
                      << "\n, ans: " << leetcode::to_string(ans) << "\n";
        }
    }
    return 0;
}
