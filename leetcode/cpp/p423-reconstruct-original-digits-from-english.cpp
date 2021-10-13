// LeetCode 423. Reconstruct original digits from English.
#include <algorithm>
#include <iostream>

class Solution {
public:
    std::string originalDigits(const std::string& s)
    {
        size_t letter_counts[127] = { 0 };
        for (const auto c : s) {
            ++letter_counts[static_cast<int>(c)];
        }
        const auto num_0 = letter_counts['z'];
        const auto num_2 = letter_counts['w'];
        const auto num_4 = letter_counts['u'];
        const auto num_6 = letter_counts['x'];
        const auto num_8 = letter_counts['g'];

        const auto num_1 = letter_counts['o'] - num_0 - num_2 - num_4;
        const auto num_3 = letter_counts['h'] - num_8;
        const auto num_5 = letter_counts['f'] - num_4;
        const auto num_7 = letter_counts['s'] - num_6;

        const size_t ret_size = letter_counts['o']
            + letter_counts['i']
            + letter_counts['h']
            + letter_counts['s']
            - letter_counts['g']
            - letter_counts['x'];

        std::string ret(ret_size, '9');
        auto it = ret.begin();
        it = std::fill_n(it, num_0, '0');
        it = std::fill_n(it, num_1, '1');
        it = std::fill_n(it, num_2, '2');
        it = std::fill_n(it, num_3, '3');
        it = std::fill_n(it, num_4, '4');
        it = std::fill_n(it, num_5, '5');
        it = std::fill_n(it, num_6, '6');
        it = std::fill_n(it, num_7, '7');
        it = std::fill_n(it, num_8, '8');
        return ret;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::string s;
        std::string exp;
    };
    const TestCase testCases[] = {
        { "owoztneoer", "012" },
        { "fviefuro", "45" },
        { "nineeightsevensixfivefourthreetwoonezero", "0123456789" },
        { "zero", "0" },
        { "zerozero", "00" },
        { "one", "1" },
        { "two", "2" },
        { "three", "3" },
        { "four", "4" },
        { "five", "5" },
        { "six", "6" },
        { "seven", "7" },
        { "eight", "8" },
        { "nine", "9" },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.originalDigits(tc.s);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(s: " << tc.s << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
