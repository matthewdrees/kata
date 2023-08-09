// LeetCode 62. Unique Paths.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    int uniquePaths(int m, int n)
    {
        assert(m >= 1 && m <= 100);
        assert(n >= 1 && n <= 100);
        const size_t X = static_cast<size_t>(std::max(m, n));
        const size_t Y = static_cast<size_t>(std::min(m, n));
        std::vector<int> v(X, 1);
        for (size_t y = 1; y < Y; ++y) {
            for (size_t x = 1; x < X; ++x) {
                v[x] = v[x - 1] + v[x];
            }
        }
        return v.back();
    }
};

int main()
{
    struct TestCase {
        int m;
        int n;
        int exp;
    };

    const TestCase test_cases[] = {
        { 1, 1, 1 },
        { 1, 2, 1 },
        { 2, 1, 1 },
        { 2, 2, 2 },
        { 2, 3, 3 },
        { 3, 2, 3 },
        { 3, 3, 6 },
        { 4, 4, 20 },
        { 3, 7, 28 },
        { 7, 3, 28 },
        { 15, 21, 1391975640 },
        { 16, 20, 1855967520 },
        { 17, 18, 1166803110 },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.uniquePaths(tc.m, tc.n);
        if (tc.exp != act) {
            std::cerr << "fail, m: " << tc.m
                      << ", n: " << tc.n
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}