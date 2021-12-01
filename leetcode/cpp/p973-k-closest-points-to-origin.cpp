// LeetCode 973. K closest points to origin.
#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k)
    {
        assert(k > 0 && static_cast<size_t>(k) <= points.size());
        std::nth_element(points.begin(), points.begin() + k - 1, points.end(), [](const auto& p1, const auto& p2) {
            return p1[0] * p1[0] + p1[1] * p1[1] < p2[0] * p2[0] + p2[1] * p2[1];
        });
        points.erase(points.begin() + k, points.end());
        return points;
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> points;
        int k;
        std::vector<std::vector<int>> exp;
    };
    const TestCase testCases[] = {
        { { { 1, 3 }, { -2, 2 } }, 1, { { -2, 2 } } },
        { { { 3, 3 }, { 5, -1 }, { -2, 4 } }, 2,
            { { 3, 3 }, { -2, 4 } } },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        auto points = tc.points;
        const auto ans = solution.kClosest(points, tc.k);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(num points: " << leetcode::to_string(tc.points) << ", k: " << tc.k << ")"
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", ans: " << leetcode::to_string(ans)
                      << "\n";
        }
    }
    return 0;
}
