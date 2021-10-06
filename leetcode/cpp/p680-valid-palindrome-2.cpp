// LeetCode 680. Valid palindrome 2.
#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <random>

static bool is_palendrome(const std::string& s, size_t i, size_t j, bool first_pass)
{
    for (; i < j; ++i, --j) {
        if (s[i] != s[j]) {
            if (first_pass) {
                return is_palendrome(s, i + 1, j, false) || is_palendrome(s, i, j - 1, false);
            } else {
                return false;
            }
        }
    }
    return true;
}

class Solution {
public:
    bool validPalindrome(const std::string& s)
    {
        return is_palendrome(s, 0, s.size() - 1, true);
    }
};

class Solution2 {
public:
    bool validPalindrome(const std::string& s)
    {
        assert(!s.empty());
        size_t i = 0;
        size_t j = s.size() - 1;
        for (; i < j && s[i] == s[j]; ++i, --j) { }
        if (i >= j) {
            return true;
        }
        const size_t I = i;
        const size_t J = j;
        for (i = I, j = J - 1; i < j && s[i] == s[j]; ++i, --j) { }
        if (i >= j) {
            return true;
        }
        for (i = I + 1, j = J; i < j && s[i] == s[j]; ++i, --j) { }
        if (i >= j) {
            return true;
        }
        return false;
    }
};

// Generate a palindrome string with 1 character wrong for test data.
//
// \param half_len: size of returned palindrome string is actually half_len * 2 + 1.
std::string get_test_string(size_t half_len)
{
    const std::string chars = "abcdefg"; // Should be enough.
    std::mt19937 mt(0); // Seed = 0, we want the same values each time.
    std::uniform_int_distribution<> dist(0, chars.size() - 1);
    auto result = std::string(half_len * 2 + 1, 'z');

    // Fill in first half of string with random letters.
    std::generate_n(begin(result), half_len, [&]() { return chars[dist(mt)]; });

    // Copy it in reverse to last half of string.
    std::reverse_copy(begin(result), begin(result) + half_len, begin(result) + half_len + 1);

    // Rotate the middle character to a quarter way up to the front.
    const auto middle = result.begin() + result.size() / 2;
    const auto quarter = result.begin() + result.size() / 4;
    std::rotate(quarter, middle, middle + 1);

    return result;
}

static void BM_mine(benchmark::State& state)
{
    std::string s = get_test_string(state.range(0));
    Solution solution;
    for (auto _ : state)
        benchmark::DoNotOptimize(solution.validPalindrome(s));
}
BENCHMARK(BM_mine)->Range(0, 25'000);

static void BM_other(benchmark::State& state)
{
    std::string s = get_test_string(state.range(0));
    Solution2 solution;
    for (auto _ : state)
        benchmark::DoNotOptimize(solution.validPalindrome(s));
}
BENCHMARK(BM_other)->Range(0, 25'000);

BENCHMARK_MAIN();

int main2(int argc, char* argv[])
{
    struct TestCase {
        std::string s;
        bool exp;
    };
    const TestCase testCases[] = {
        { "a", true },
        { "ab", true },
        { "abc", false },
        { "aba", true },
        { "aba", true },
        { "bdbd", true },
        { "eedede", true },
        { "ededee", true },
        { "amanaplanacanalpanama", true },
        { "zamanaplanacanalpanama", true },
        { "amanaplanacanalpanamaz", true },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.validPalindrome(tc.s);
        if (tc.exp != ans) {
            std::cout << "FAIL." << __FUNCTION__ << ", (s: " << tc.s << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
