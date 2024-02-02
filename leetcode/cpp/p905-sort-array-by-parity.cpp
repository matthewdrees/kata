// LeetCode 905. Sort Array By Parity.
#include "leetcode.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> sortArrayByParity(std::vector<int>& nums)
    {
        // (void)std::partition(nums.begin(), nums.end(), [](auto n) { return n % 2 == 0; });
        if (nums.empty()) {
            return nums;
        }
        size_t s1 = 0;
        size_t s2 = nums.size() - 1;
        while (true) {
            for (; s1 < s2; ++s1) {
                if (nums[s1] % 2 != 0) {
                    break;
                }
            }

            for (; s2 > s1; --s2) {
                if (nums[s2] % 2 == 0) {
                    break;
                }
            }

            if (s1 >= s2) {
                break;
            }
            std::swap(nums[s1], nums[s2]);
            ++s1;
            --s2;
        }
        return nums;
    }
};

class Solution2 {
public:
    std::vector<int> sortArrayByParity(std::vector<int>& nums)
    {
        if (nums.empty()) {
            return nums;
        }
        auto it1 = nums.begin();
        auto it2 = nums.end() - 1;
        while (it1 != it2) {
            it1 = std::find_if(it1, it2, [](auto n) { return n % 2 != 0; });
            for (; it1 != it2; --it2) {
                if (*it2 % 2 == 0) {
                    break;
                }
            }
            if (it1 != it2) {
                std::swap(*it1, *it2);
                ++it1;
                if (it1 != it2) {
                    --it2;
                }
            }
        }
        return nums;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        std::vector<int> exp;
    };

    const TestCase test_cases[] = {
        { {}, {} },
        { { 1 }, { 1 } },
        { { 1, 2 }, { 2, 1 } },
        { { 2, 1 }, { 2, 1 } },
        { { 3, 1, 2, 4 }, { 4, 2, 1, 3 } },
    };

    Solution2 solution;
    for (const auto& tc : test_cases) {
        auto copy = tc.nums;
        const auto act = solution.sortArrayByParity(copy);
        if (tc.exp != act) {
            std::cerr << "Fail. nums: " << leetcode::to_string(tc.nums)
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
}