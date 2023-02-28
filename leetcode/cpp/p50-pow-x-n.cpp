// LeetCode p50. Pow(x, n).

#include <iostream>

// Exponent by squaring algorithm, with check for -x already done.
double exp_by_squaring_positive(double x, int64_t n)
{
    if (n == 0) {
        return 1.0;
    }
    if (n % 2 == 0) {
        return exp_by_squaring_positive(x * x, n / 2);
    }
    return x * exp_by_squaring_positive(x * x, (n - 1) / 2);
}

class Solution {
public:
    double myPow(double x, int n)
    {
        if (n == 0) {
            return 1.0;
        }
        if (x == 0.0) {
            return 0.0;
        }
        if (n < 0) {
            int64_t n64 = n;
            return exp_by_squaring_positive(1 / x, -n64);
        }
        return exp_by_squaring_positive(x, n);
    }
};

int main()
{
    struct TestCase {
        double x;
        int n;
        double exp;
    };

    const TestCase test_cases[] = {
        { 2.0, 10, 1024.0 },
        { 2.1, 3, 9.261 },
        { 2.0, -2, 0.25 },
        { 0.0, 0, 1.0 },
        { 2.0, 0, 1.0 },
        { -2.0, 0, 1.0 },
        { -2.0, 1, -2.0 },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.myPow(tc.x, tc.n);
        if (tc.exp != act) {
            std::cerr << "Fail, x: " << tc.x
                      << ", n: " << tc.n
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}