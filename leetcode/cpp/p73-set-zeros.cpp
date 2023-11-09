// LeetCode 73. Set zeros.
#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

static bool is_first_col_zero(const Matrix& matrix)
{
    for (size_t y = 0; y < matrix.size(); ++y) {
        if (matrix[y][0] == 0) {
            return true;
        }
    }
    return false;
}

static void set_col_zero(Matrix& matrix, size_t Y, size_t col)
{
    for (size_t y = 0; y < Y; ++y) {
        matrix[y][col] = 0;
    }
}

class Solution {
public:
    void setZeroes(Matrix& matrix)
    {
        const auto Y = matrix.size();
        assert(Y > 0);
        const auto X = matrix[0].size();
        assert(X > 0);

        const bool first_col_is_zero = is_first_col_zero(matrix);
        for (auto& row : matrix) {
            if (std::ranges::any_of(row, [](int n) { return n == 0; })) {
                row[0] = 0;
            }
        }

        for (size_t x = 1; x < X; ++x) {
            for (size_t y = 0; y < Y; ++y) {
                if (matrix[y][x] == 0) {
                    set_col_zero(matrix, Y, x);
                    break;
                }
            }
        }

        for (auto& row : matrix) {
            if (row[0] == 0) {
                std::fill(row.begin() + 1, row.end(), 0);
            }
        }

        if (first_col_is_zero) {
            set_col_zero(matrix, Y, 0);
        }
    }
};

int main()
{
    struct TestCase {
        Matrix matrix;
        Matrix exp;
    };

    const TestCase test_cases[] = {
        { { { 0 } }, { { 0 } } },
        { { { 1 } }, { { 1 } } },
        { { { 1, 1 } }, { { 1, 1 } } },
        { { { 0, 1 } }, { { 0, 0 } } },
        { { { 1, 0 } }, { { 0, 0 } } },
        { { { 1 },
              { 1 } },
            { { 1 },
                { 1 } } },
        { { { 0 },
              { 1 } },
            { { 0 },
                { 0 } } },
        { { { 1 },
              { 0 } },
            { { 0 },
                { 0 } } },
        { { { 1, 1 },
              { 1, 1 } },
            { { 1, 1 },
                { 1, 1 } } },
        { { { 0, 1 },
              { 1, 1 } },
            { { 0, 0 },
                { 0, 1 } } },
        { { { 1, 0 },
              { 1, 1 } },
            { { 0, 0 },
                { 1, 0 } } },
        { { { 1, 1 },
              { 0, 1 } },
            { { 0, 1 },
                { 0, 0 } } },
        { { { 1, 1 },
              { 1, 0 } },
            { { 1, 0 },
                { 0, 0 } } },
        { { { 1, 1, 1 },
              { 1, 0, 1 },
              { 1, 1, 1 } },
            { { 1, 0, 1 },
                { 0, 0, 0 },
                { 1, 0, 1 } } },
        { { { 0, 1, 2, 0 },
              { 3, 4, 5, 2 },
              { 1, 3, 1, 5 } },
            { { 0, 0, 0, 0 },
                { 0, 4, 5, 0 },
                { 0, 3, 1, 0 } } },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        auto matrix = tc.matrix;
        solution.setZeroes(matrix);
        if (tc.exp != matrix) {
            std::cerr << "FAIL, matix: " << leetcode::to_string(tc.matrix)
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(matrix)
                      << "\n";
        }
    }
    return 0;
}