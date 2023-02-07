// LeetCode 69. Sqrt(x).

#include <iostream>
#include <limits>

class Solution {
public:
    int mySqrt(int x)
    {
        if (x >= 2147395600) {
            return 46340;
        }
        int64_t ans = 0;
        int64_t base = 32768; // 2^15
        int64_t factor = 16384; // 2^14
        while (true) {
            const int64_t n = base * base;
            if (n == x) {
                ans = base;
                break;
            } else if (n < x) {
                ans = base;
                base += factor;
            } else {
                base -= factor;
            }
            if (factor == 0) {
                break;
            }
            factor >>= 1;
        }
        return static_cast<int>(ans);
    }
};

int main()
{
    struct TestCase {
        int x;
        int exp;
    };

    TestCase test_cases[] = {
        { 0, 0 },
        { 1, 1 },
        { 2, 1 },
        { 3, 1 },
        { 4, 2 },
        { 5, 2 },
        { 8, 2 },
        { 9, 3 },
        { 10, 3 },
        { 15, 3 },
        { 16, 4 },
        { 24, 4 },
        { 25, 5 },
        { 35, 5 },
        { 36, 6 },
        { 48, 6 },
        { 49, 7 },
        { 63, 7 },
        { 64, 8 },
        { std::numeric_limits<int>::max(), 46340 },
        { 2147395599, 46339 },
        { 2147395600, 46340 },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.mySqrt(tc.x);
        if (tc.exp != act) {
            std::cerr << "fail: " << tc.x << ", "
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}