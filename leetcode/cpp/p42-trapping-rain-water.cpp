// LeetCode 42. Trapping rain water.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "leetcode.hpp"

class Solution {
public:
    int trap(const std::vector<int>& height)
    {
        std::vector<int> v = height;

        // Change v to be a running maximum from right to left.
        int rmax = 0;
        for (auto it = rbegin(v); it != rend(v); ++it) {
            rmax = std::max(rmax, *it);
            *it = rmax;
        }

        // Change v to be water amounts.
        int lmax = 0;
        std::transform(begin(height), end(height), begin(v), begin(v), [&](const auto h, const auto rmax) {
            lmax = std::max(h, lmax);
            const int water_level = std::min(lmax, rmax);
            return water_level - h;
        });

        // Now add up the water amounts.
        return std::reduce(begin(v), end(v), 0);
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::vector<int> height;
        int exp;
    };
    const TestCase testCases[] = {
        { {}, 0 },
        { { 0 }, 0 },
        { { 1 }, 0 },
        { { 1, 2 }, 0 },
        { { 2, 1 }, 0 },
        { { 1, 1, 1 }, 0 },
        { { 1, 2, 1 }, 0 },
        { { 2, 2, 1 }, 0 },
        { { 2, 2, 2 }, 0 },
        { { 2, 1, 2 }, 1 },
        { { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 }, 6 },
        { { 4, 2, 0, 3, 2, 5 }, 9 },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.trap(tc.height);
        if (tc.exp != ans) {
            std::cout << "FAIL. height: " << leetcode::to_string(tc.height)
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
