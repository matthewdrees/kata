// LeetCode 29. Divide Two Integers
#include <cmath>
#include <iostream>
#include <limits>

class Solution {
public:
    int divide(int dividend, int divisor)
    {
        int64_t numerator = llabs(dividend);
        const int64_t denominator = llabs(divisor);
        size_t base2 = 0;
        for (; base2 < 32; ++base2) {
            const int64_t step = denominator << base2;
            if (step > numerator) {
                break;
            }
        }
        int64_t ans = 0;
        while (base2-- > 0) {
            const int64_t step = denominator << base2;
            if (numerator >= step) {
                numerator -= step;
                ans += (1L << base2);
                if (numerator == 0) {
                    break;
                }
            }
        }
        const bool is_positive = (dividend < 0) == (divisor < 0);
        if (is_positive) {
            if (ans > std::numeric_limits<int32_t>::max()) {
                return std::numeric_limits<int32_t>::max();
            }
            return ans;
        }
        return -ans;
    }
};

int main()
{
    struct TestCase {
        int dividend;
        int divisor;
        int exp;
    };

    TestCase testCases[] = {
        { 10, 3, 3 },
        { 7, -3, -2 },
        { 0, 1, 0 },
        { 1, 1, 1 },
        { 100, 2, 50 },
        { 101, 2, 50 },
        { 102, 2, 51 },
        { -100, 2, -50 },
        { 100, -2, -50 },
        { 100, -2, -50 },
        { 2147483647, 2147483647, 1 },
        { -2147483648, -2147483648, 1 },
        { -2147483648, 1, -2147483648 },
        { -2147483648, -1, 2147483647 },
        { 2, 3, 0 },
        { 3, 3, 1 },
        { 5, 3, 1 },
        { 6, 3, 2 },
        { 8, 3, 2 },
        { 9, 3, 3 },
        { 11, 3, 3 },
        { 12, 3, 4 },
        { 0, 1, 0 },
    };
    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.divide(tc.dividend, tc.divisor);
        if (tc.exp != ans) {
            std::cout << "FAIL. prices: (dividend: " << tc.dividend
                      << ", divisor: " << tc.divisor << ")"
                      << ", exp: " << tc.exp << ", ans: " << ans << "\n";
        }
    }
}
