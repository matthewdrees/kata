// LeetCode 62. Unique Paths.
#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    int uniquePathsWithObstacles(const std::vector<std::vector<int>>& obstacleGrid)
    {
        assert(!obstacleGrid.empty());
        assert(!obstacleGrid[0].empty());
        const size_t Y = obstacleGrid.size();
        const size_t X = obstacleGrid[0].size();
        std::vector<int> v(X, 1);
        {
            auto offset = std::find(obstacleGrid[0].begin(), obstacleGrid[0].end(), 1) - obstacleGrid[0].begin();
            std::fill(v.begin() + offset, v.end(), 0);
        }
        for (size_t y = 1; y < Y; ++y) {
            if (obstacleGrid[y][0] == 1) {
                v[0] = 0;
            }
            for (size_t x = 1; x < X; ++x) {
                if (obstacleGrid[y][x] == 1) {
                    v[x] = 0;
                } else {
                    v[x] = v[x - 1] + v[x];
                }
            }
        }
        return v.back();
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> v;
        int exp;
    };

    const TestCase test_cases[] = {
        { { { 1 } }, 0 },
        { { { 0 } }, 1 },
        { { { 0, 1 }, { 1, 0 } }, 0 },
        { { { 0, 0 }, { 1, 0 } }, 1 },
        { { { 0, 1 }, { 0, 0 } }, 1 },
        { { { 0, 0 }, { 0, 0 } }, 2 },
        { { { 0, 0, 0 }, { 0, 0, 0 } }, 3 },
        { { { 1, 0, 0 }, { 0, 0, 0 } }, 0 },
        { { { 0, 1, 0 }, { 0, 0, 0 } }, 1 },
        { { { 0, 0, 1 }, { 0, 0, 0 } }, 2 },
        { { { 0, 0, 0 }, { 1, 0, 0 } }, 2 },
        { { { 0, 0, 0 }, { 0, 1, 0 } }, 1 },
        { { { 0, 0, 0 }, { 0, 0, 1 } }, 0 },
        { { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, 6 },
        { { { 1, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, 0 },
        { { { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, 3 },
        { { { 0, 0, 1 }, { 0, 0, 0 }, { 0, 0, 0 } }, 5 },
        { { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 0 } }, 3 },
        { { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } }, 2 },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.uniquePathsWithObstacles(tc.v);
        if (tc.exp != act) {
            std::cerr << "fail, v: " << leetcode::to_string(tc.v)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}