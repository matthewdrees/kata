// LeetCode 64. Minimum Path Sum.
#include "leetcode.hpp"

#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    int minPathSum(const std::vector<std::vector<int>>& grid)
    {
        const size_t Y = grid.size();
        assert(Y != 0);
        const size_t X = grid[0].size();
        assert(X != 0);
        std::vector<int> v = grid[0];
        for (size_t x = 1; x < X; ++x) {
            v[x] += v[x - 1];
        }
        for (size_t y = 1; y < Y; ++y) {
            const auto& row = grid[y];
            assert(row.size() == v.size());
            v[0] += row[0];
            for (size_t x = 1; x < X; ++x) {
                v[x] = row[x] + std::min(v[x - 1], v[x]);
            }
        }
        return v.back();
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> grid;
        int exp;
    };

    const TestCase test_cases[] = {
        { { { 0 } }, 0 },
        { { { 1 } }, 1 },
        { { { 1, 3 }, { 1, 1 } }, 3 },
        { { { 1, 4 }, { 2, 1 } }, 4 },
        { { { 0, 0, 0 }, { 0, 0, 0 } }, 0 },
        { { { 1, 1, 2 }, { 2, 1, 1 } }, 4 },
        { { { 1, 2, 1 }, { 1, 1, 1 } }, 4 },
        { { { 1, 1, 1 }, { 2, 2, 1 } }, 4 },
        { { { 1, 1 }, { 2, 1 }, { 2, 1 } }, 4 },
        { { { 1, 2 }, { 1, 1 }, { 2, 1 } }, 4 },
        { { { 1, 2 }, { 1, 2 }, { 1, 1 } }, 4 },
        { { { 1, 1, 1 }, { 2, 2, 1 }, { 1, 2, 1 } }, 5 },
        { { { 1, 1, 2 }, { 2, 1, 1 }, { 1, 2, 1 } }, 5 },
        { { { 1, 1, 2 }, { 2, 1, 2 }, { 1, 1, 1 } }, 5 },
        { { { 1, 2, 2 }, { 1, 1, 1 }, { 2, 2, 1 } }, 5 },
        { { { 1, 2, 2 }, { 1, 1, 2 }, { 2, 1, 1 } }, 5 },
        { { { 1, 2, 1 }, { 1, 2, 1 }, { 1, 1, 1 } }, 5 },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.minPathSum(tc.grid);
        if (tc.exp != act) {
            std::cerr << "fail, grid: " << leetcode::to_string(tc.grid)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}
