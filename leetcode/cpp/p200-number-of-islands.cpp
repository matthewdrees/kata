// LeetCode 200. Number of Islands.
#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<char>>;

static void fill_zero(Grid& grid, size_t x, size_t y)
{
    if (grid[y][x] == '0') {
        return;
    }
    grid[y][x] = '0';
    if (x > 0) {
        fill_zero(grid, x - 1, y);
    }
    if (x + 1 < grid[y].size()) {
        fill_zero(grid, x + 1, y);
    }
    if (y > 0) {
        fill_zero(grid, x, y - 1);
    }
    if (y + 1 < grid.size()) {
        fill_zero(grid, x, y + 1);
    }
}

class Solution {
public:
    int numIslands(Grid& grid)
    {
        int num_islands = 0;
        for (size_t y = 0; y < grid.size(); ++y) {
            const auto& row = grid[y];
            for (size_t x = 0; x < row.size(); ++x) {
                if (row[x] == '1') {
                    ++num_islands;
                    fill_zero(grid, x, y);
                }
            }
        }
        return num_islands;
    }
};

int main()
{
    struct TestCase {
        Grid grid;
        int exp;
    };

    const TestCase test_cases[] = {
        {
            {
                { '1', '1', '1', '1', '0' },
                { '1', '1', '0', '1', '0' },
                { '1', '1', '0', '0', '0' },
                { '0', '0', '0', '0', '0' },
            },
            1,
        },
        {
            {
                { '1', '1', '0', '0', '0' },
                { '1', '1', '0', '0', '0' },
                { '0', '0', '1', '0', '0' },
                { '0', '0', '0', '1', '1' },
            },
            3,
        },
        {
            {
                { '1', '1', '0', '0', '0' },
                { '1', '0', '0', '0', '0' },
                { '0', '0', '1', '0', '0' },
                { '0', '0', '0', '0', '1' },
            },
            3,
        }
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        auto grid_copy = tc.grid;
        const auto act = solution.numIslands(grid_copy);
        if (tc.exp != act) {
            std::cerr << "fail, exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}
