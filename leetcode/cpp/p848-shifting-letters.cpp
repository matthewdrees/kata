// LeetCode 848. Shifting letters.
#include <benchmark/benchmark.h>

#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    std::string shiftingLetters(std::string s, const std::vector<int>& shifts)
    {
        int64_t carry = 0;
        for (size_t i = shifts.size(); i-- > 0;) {
            carry += shifts[i];
            s[i] = (s[i] + carry - 97) % 26 + 97;
        }
        return s;
    }
};

// Otherwise the "fastest" <cough> solution posted on leetcode for comparing benchmarks.
class Solution2 {
public:
    std::string shiftingLetters(std::string s, std::vector<int>& shifts)
    {
        int len = shifts.size();
        int sum = 0;
        std::string res = "";
        for (int num : shifts) {
            num %= 26;
            sum += num;
            sum %= 26;
        }
        for (int i = 0; i < s.length(); i++) {
            if (i >= len)
                return res;
            int curr = s[i] - 'a';
            curr += sum;
            curr %= 26;
            res += curr + 'a';
            int temp = shifts[i] % 26;
            sum -= temp;
            if (sum < 0)
                sum += 26;
        }
        return res;
    }
};

static std::string to_string(const std::vector<int>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v) {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

// Less than 1 billion but prime so interesting for shifting and getting different letters.
const int large_prime_number = 179'424'691;

static void BM_mine(benchmark::State& state)
{
    std::string s(state.range(0), 'a');
    std::vector<int> shifts(state.range(0), large_prime_number);
    Solution solution;
    for (auto _ : state)
        benchmark::DoNotOptimize(solution.shiftingLetters(s, shifts));
}
BENCHMARK(BM_mine)->Range(0, 10'000);

static void BM_other(benchmark::State& state)
{
    std::string s(state.range(0), 'a');
    std::vector<int> shifts(state.range(0), large_prime_number);
    Solution2 solution;
    for (auto _ : state)
        benchmark::DoNotOptimize(solution.shiftingLetters(s, shifts));
}
BENCHMARK(BM_other)->Range(0, 10'000);

BENCHMARK_MAIN();

int main2()
{
    struct TestCase {
        std::string s;
        std::vector<int> shifts;
        std::string expected;
    };
    TestCase testCases[] = {
        { "", {}, "" },
        { "a", { 1 }, "b" },
        { "t", { 1 }, "u" },
        { "z", { 1 }, "a" },
        { "abc", { 3, 5, 9 }, "rpl" },
        { "aaa", { 1, 2, 3 }, "gfd" },
    };
    Solution s;
    for (const auto& tc : testCases) {
        const auto actual = s.shiftingLetters(tc.s, tc.shifts);
        if (tc.expected != actual) {
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(s: " << tc.s << ", shifts: " << to_string(tc.shifts) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return 0;
}
