// LeetCode 48. Rotate Image.
#include <iostream>
#include <vector>

#include "leetcode.hpp"

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix)
    {
        size_t lo = 0;
        size_t hi = matrix.size() - 1;
        for (; lo < hi; ++lo, --hi) {
            for (size_t i = 0; i < hi - lo; ++i) {
                int& p1 = matrix[lo][lo + i];
                int& p2 = matrix[hi - i][lo];
                int& p3 = matrix[hi][hi - i];
                int& p4 = matrix[lo + i][hi];
                auto tmp = p1;
                p1 = p2;
                p2 = p3;
                p3 = p4;
                p4 = tmp;
            }
        }
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> matrix;
        std::vector<std::vector<int>> exp;
    };

    TestCase test_cases[] = {
        { { { 5 } }, { { 5 } } },
        { { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } }, { { 7, 4, 1 }, { 8, 5, 2 }, { 9, 6, 3 } } },
        {
            { { 5, 1, 9, 11 }, { 2, 4, 8, 10 }, { 13, 3, 6, 7 }, { 15, 14, 12, 16 } },
            { { 15, 13, 2, 5 }, { 14, 3, 4, 1 }, { 12, 6, 8, 9 }, { 16, 7, 10, 11 } },
        },
        {
            {
                { 1, 2, 3, 4, 5 },
                { 6, 7, 8, 9, 10 },
                { 11, 12, 13, 14, 15 },
                { 16, 17, 18, 19, 20 },
                { 21, 22, 23, 24, 25 },
            },
            {
                { 21, 16, 11, 6, 1 },
                { 22, 17, 12, 7, 2 },
                { 23, 18, 13, 8, 3 },
                { 24, 19, 14, 9, 4 },
                { 25, 20, 15, 10, 5 },
            },
        },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        auto act = tc.matrix;
        solution.rotate(act);
        if (tc.exp != act) {
            std::cerr << "Fail"
                      << ", matrix: " << leetcode::to_string(tc.matrix)
                      << ", exp: " << leetcode::to_string(tc.matrix)
                      << ", act: " << leetcode::to_string(tc.matrix)
                      << "\n";
        }
    }
}