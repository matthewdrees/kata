// LeetCode 46. Permutations.
#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using Perms = std::vector<std::vector<int>>;

void cycle3(Perms& perms, std::vector<int>& nums)
{
    auto it1 = nums.end() - 3;
    auto it2 = nums.end() - 2;
    auto it3 = nums.end() - 1;
    perms.push_back(nums);
    std::swap(*it2, *it3);
    perms.push_back(nums);
    std::rotate(it1, it3, nums.end());
    perms.push_back(nums);
    std::swap(*it2, *it3);
    perms.push_back(nums);
    std::rotate(it1, it2, nums.end());
    perms.push_back(nums);
    std::swap(*it2, *it3);
    perms.push_back(nums);
    std::swap(*it1, *it3);
}
void cycle4(Perms& perms, std::vector<int>& nums)
{
    const auto it = nums.end() - 4;
    for (size_t _ = 0; _ < 4; ++_) {
        cycle3(perms, nums);
        std::rotate(it, it + 1, nums.end());
    }
}
void cycle5(Perms& perms, std::vector<int>& nums)
{
    auto it = nums.end() - 5;
    for (size_t _ = 0; _ < 5; ++_) {
        cycle4(perms, nums);
        std::rotate(it, it + 1, nums.end());
    }
}

void cycle6(Perms& perms, std::vector<int>& nums)
{
    auto it = nums.end() - 6;
    for (size_t _ = 0; _ < 6; ++_) {
        cycle5(perms, nums);
        std::rotate(it, it + 1, nums.end());
    }
}
class Solution {
public:
    Perms permute(std::vector<int>& nums)
    {
        Perms perms;
        switch (nums.size()) {
        case 1:
            perms.push_back(nums);
            break;
        case 2:
            perms.push_back(nums);
            perms.push_back({ nums[1], nums[0] });
            break;
        case 3:
            cycle3(perms, nums);
            break;
        case 4:
            cycle4(perms, nums);
            break;
        case 5:
            cycle5(perms, nums);
            break;
        case 6:
            cycle6(perms, nums);
            break;
        }
        return perms;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        Perms exp;
    };

    const TestCase test_cases[] = {
        { { 5 }, { { 5 } } },
        { { 1, 2 }, { { 1, 2 }, { 2, 1 } } },
        { { 1, 2, 3 }, { { 1, 2, 3 }, { 1, 3, 2 }, { 2, 1, 3 }, { 2, 3, 1 }, { 3, 1, 2 }, { 3, 2, 1 } } },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        auto nums = tc.nums;
        const auto act = solution.permute(nums);
        if (tc.exp != act) {
            std::cerr << "Fail, nums: " << leetcode::to_string(tc.nums)
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
    std::vector<int> nums5 { 0, 1, 2, 3, 4, 5 };
    auto ans5 = solution.permute(nums5);
    std::cout << leetcode::to_string(ans5) << "\n";
    std::cout << ans5.size() << "\n";
}