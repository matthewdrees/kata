// LeetCode 59. Spiral Matrix II.
#include "leetcode.hpp"

#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        assert(n >= 1 && n <= 20);
        int num = 1;
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        size_t dim0 = 0;
        size_t dim1 = static_cast<size_t>(n);
        for (; dim0 < dim1; ++dim0, --dim1) {
            for (auto x = dim0; x < dim1; ++x) {
                matrix[dim0][x] = num++;
            }
            for (auto y = dim0 + 1; y < dim1 - 1; ++y) {
                matrix[y][dim1 - 1] = num++;
            }
            for (auto x = dim1 - 1; x > dim0; --x) {
                matrix[dim1 - 1][x] = num++;
            }
            for (auto y = dim1 - 1; y > dim0; --y) {
                matrix[y][dim0] = num++;
            }
        }
        return matrix;
    }
};

int main()
{
    struct TestCase {
        int n;
        std::vector<std::vector<int>> exp;
    };

    const TestCase test_cases[] = {
        { 1, { { 1 } } },
        { 2, { { 1, 2 }, { 4, 3 } } },
        { 3, { { 1, 2, 3 }, { 8, 9, 4 }, { 7, 6, 5 } } },
        { 4, { { 1, 2, 3, 4 }, { 12, 13, 14, 5 }, { 11, 16, 15, 6 }, { 10, 9, 8, 7 } } }
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.generateMatrix(tc.n);
        if (tc.exp != act) {
            std::cerr << "Fail, n: " << tc.n
                      << ", exp: \n"
                      << leetcode::to_string(tc.exp)
                      << "\n, act: \n"
                      << leetcode::to_string(act)
                      << "\n";
        }
    }
    return 0;
}