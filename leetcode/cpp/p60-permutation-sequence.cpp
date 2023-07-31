// LeetCode 60. Permutation Sequence.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

const int MAX_N = 9;
int factorial(int n)
{
    assert(n >= 0);
    assert(n <= MAX_N);
    static int facts[MAX_N + 1] = {
        0,
        1,
        2,
        6,
        24,
        120,
        720,
        5040,
        40320,
        362880
    };
    return facts[static_cast<size_t>(n)];
}

class Solution {
public:
    std::string getPermutation(int n, int k)
    {
        assert(n >= 1 && n <= MAX_N);
        assert(k >= 1 && k <= 362880);
        k -= 1;
        std::string s(static_cast<size_t>(n), ' ');
        std::iota(s.begin(), s.end(), '1');
        std::string ans;
        for (int i = n - 1; i > 0; --i) {
            const int div = factorial(i);
            const int idx = k / div;
            k = k % div;
            ans += s[static_cast<size_t>(idx)];
            s.erase(static_cast<size_t>(idx), 1);
        }
        ans += s[0];
        return ans;
    }
};

int main()
{
    struct TestCase {
        int n;
        int k;
        std::string exp;
    };
    TestCase test_cases[] = {
        { 1, 1, "1" },
        { 2, 1, "12" },
        { 2, 2, "21" },
        { 3, 1, "123" },
        { 3, 2, "132" },
        { 3, 3, "213" },
        { 3, 4, "231" },
        { 3, 5, "312" },
        { 3, 6, "321" },
        { 4, 1, "1234" },
        { 4, 2, "1243" },
        { 4, 9, "2314" },
        { 4, 24, "4321" },
        { 5, 1, "12345" },
        { 5, 120, "54321" },
        { 6, 1, "123456" },
        { 6, 720, "654321" },
        { 7, 1, "1234567" },
        { 7, 5040, "7654321" },
        { 8, 1, "12345678" },
        { 8, 40320, "87654321" },
        { 9, 1, "123456789" },
        { 9, 2, "123456798" },
        { 9, 362880, "987654321" },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.getPermutation(tc.n, tc.k);
        if (tc.exp != act) {
            std::cerr << "fail, n: " << tc.n
                      << ", k: " << tc.k
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}