// LeetCode 54. Spiral Matrix.
// #include <benchmark/benchmark.h>

#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
    {
        size_t y_max = matrix.size();
        assert(y_max >= 1);
        size_t x_max = matrix[0].size();
        assert(x_max >= 1);
        size_t y_min = 0;
        size_t x_min = 0;
        std::vector<int> v(x_max * y_max);
        auto it = v.begin();
        while (true) {
            // right
            {
                const auto& v2 = matrix[y_min];
                it = std::copy(v2.begin() + x_min, v2.begin() + x_max, it);
                if (it == v.end()) {
                    break;
                }
                --x_max;
            }

            // down
            for (size_t y = y_min + 1; y < y_max; ++y) {
                *it++ = matrix[y][x_max];
            }
            if (it == v.end()) {
                break;
            }
            --y_max;

            // left
            {
                const auto& v2 = matrix[y_max];
                it = std::reverse_copy(v2.begin() + x_min, v2.begin() + x_max, it);
                if (it == v.end()) {
                    break;
                }
            }

            // up
            for (size_t y = y_max - 1; y > y_min; --y) {
                *it++ = matrix[y][x_min];
            }
            ++x_min;
            ++y_min;
            if (it == v.end()) {
                break;
            }
        }
        return v;
    }
};

std::vector<std::vector<int>> gen_grid(size_t m, size_t n)
{
    std::vector<std::vector<int>> v;
    int i = 0;
    for (size_t y = 0; y < m; ++y) {
        std::vector<int> v2(n);
        std::iota(v2.begin(), v2.end(), i);
        i += static_cast<int>(n);
        v.push_back(std::move(v2));
    }
    return v;
}

// static void BM_one(benchmark::State& state)
// {
//     const auto v = gen_grid(state.range(0), state.range(0));
//     Solution solution;
//     for (auto _ : state) {
//         benchmark::DoNotOptimize(solution.spiralOrder(v));
//     }
// }
// BENCHMARK(BM_one)->Range(1, 10);

// BENCHMARK_MAIN();

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