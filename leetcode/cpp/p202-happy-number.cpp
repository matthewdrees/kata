// LeetCode 202. Happy Number.

#include <iostream>
#include <unordered_set>

static int sum_squares(int n)
{
    int total = 0;
    while (n != 0) {
        const auto nmod10 = n % 10;
        total += nmod10 * nmod10;
        n = n / 10;
    }
    return total;
}

class Solution {
public:
    bool isHappy(int n)
    {
        // Actually a vector might be faster.
        std::unordered_set<int> us;

        while (n != 1) {
            n = sum_squares(n);
            if (us.contains(n)) {
                return false;
            }
            us.insert(n);
        }
        return true;
    }
};

void test_sum_squares()
{
    struct TestCase {
        int n;
        int exp;
    };
    const TestCase test_cases[] = {
        { 1, 1 },
        { 2, 4 },
        { 9, 81 },
        { 19, 82 },
        { 91, 82 },
        { 91, 82 },
        { 2147483647, 260 },
    };
    for (const auto& tc : test_cases) {
        const auto act = sum_squares(tc.n);
        if (tc.exp != act) {
            std::cerr << "fail, n: " << tc.n
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}

void test_is_happy()
{
    struct TestCase {
        int n;
        bool exp;
    };
    const TestCase test_cases[] = {
        { 1, true },
        { 2, false },
        { 19, true },
        { 2147483647, false },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.isHappy(tc.n);
        if (tc.exp != act) {
            std::cerr << "fail, n: " << tc.n
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}

int main()
{
    test_sum_squares();
    test_is_happy();
    return 0;
}
