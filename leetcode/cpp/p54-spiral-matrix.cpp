// LeetCode 54. Spiral Matrix.
#include "leetcode.hpp"

#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
    {
        const size_t Y = matrix.size();
        assert(Y >= 1 && Y <= 10);
        const size_t X = matrix[0].size();
        assert(X >= 1 && X <= 10);
        enum class Dir {
            Right,
            Down,
            Left,
            Up,
        };
        size_t y = 0;
        size_t x = 0;
        size_t num_revolutions = 0;
        Dir dir = Dir::Right;
        std::vector<int> v(X * Y);
        auto it = v.begin();
        while (it != v.end()) {
            *it++ = matrix[y][x];
            switch (dir) {
            case Dir::Right:
                if (x + 1 < (X - num_revolutions)) {
                    x += 1;
                } else {
                    dir = Dir::Down;
                    y += 1;
                }
                break;
            case Dir::Down:
                if (y + 1 < (Y - num_revolutions)) {
                    y += 1;
                } else {
                    dir = Dir::Left;
                    x -= 1;
                }
                break;
            case Dir::Left:
                if (num_revolutions < x) {
                    x -= 1;
                } else {
                    num_revolutions += 1;
                    dir = Dir::Up;
                    y -= 1;
                }
                break;
            case Dir::Up:
                if (num_revolutions < y) {
                    y -= 1;
                } else {
                    dir = Dir::Right;
                    x += 1;
                }
                break;
            }
        }
        return v;
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> matrix;
        std::vector<int> exp;
    };

    const TestCase test_cases[] = {
        { { { -100 } }, { -100 } },
        { { { 1, 2 }, { 3, 4 } }, { 1, 2, 4, 3 } },
        { { { 7, 8 } }, { 7, 8 } },
        { { { 1 }, { 2 } }, { 1, 2 } },
        { { { 1, 2 }, { 3, 4 }, { 5, 6 } }, { 1, 2, 4, 6, 5, 3 } },
        { { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } }, { 1, 2, 3, 6, 9, 8, 7, 4, 5 } },
        { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }, { 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7 } },
        { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } }, { 1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10 } },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.spiralOrder(tc.matrix);
        if (tc.exp != act) {
            std::cerr << "Fail, matrix:\n"
                      << leetcode::to_string(tc.matrix)
                      << "\n, exp: \n"
                      << leetcode::to_string(tc.exp)
                      << "\n, act: \n"
                      << leetcode::to_string(act)
                      << "\n";
        }
    }
    return 0;
}