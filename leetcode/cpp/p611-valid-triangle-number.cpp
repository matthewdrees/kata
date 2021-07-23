// LeetCode problem 611. Valid Triangle Number.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    int triangleNumber(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        // Skip any leading zeros.
        const auto start = std::find_if(nums.begin(), nums.end(), [](const auto i) { return i > 0; });
        if (nums.end() - start < 3) {
            return 0;
        }
        // Actually look for triangles. a, b, and c are non-overlapping iterators in nums.
        // Scan by the middle b number.
        int num_triangles = 0;
        auto b_end = nums.end() - 1;
        for (auto b = start + 1; b != b_end; ++b) {
            // Optimization: Don't reset 'c' when you advance 'a'.
            auto c = b + 1;
            for (auto a = start; a != b; ++a) {
                // Optimization: pre-calculate a + b.
                const int a_plus_b = *a + *b;
                c = std::find_if(c, nums.end(), [=](const int i) { return a_plus_b <= i; });
                // Optimization: if c is end then all the rest of the values of a are valid triangles.
                if (c == nums.end()) {
                    num_triangles += (b - a) * (c - b - 1);
                    break;
                } else {
                    num_triangles += c - b - 1;
                }
            }
        }
        return num_triangles;
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
        { { 1 }, 0 },
        { { 1, 2 }, 0 },
        { { 1, 1, 2 }, 0 },
        { { 1, 2, 2 }, 1 },
        { { 2, 2, 3, 4 }, 3 },
        { { 4, 2, 3, 4 }, 4 },
        { { 1, 2, 4, 5, 6, 9 }, 5 },
        { { 1, 2, 3, 4, 5, 6, 7 }, 13 },
    };

    Solution s;
    for (auto& tc : testCases) {
        const auto ans = s.triangleNumber(tc.nums);
        if (tc.exp != ans) {
            std::cout << "FAIL. prices: (nums: " << toString(tc.nums) << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
