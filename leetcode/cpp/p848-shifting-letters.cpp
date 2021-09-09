// LeetCode 848. Shifting letters.
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    std::string shiftingLetters(std::string s, const std::vector<int>& shifts)
    {
        int carry = 0;
        for (size_t i = shifts.size(); i-- > 0;) {
            carry = (carry + shifts[i]) % 26;
            s[i] = (s[i] + carry - 97) % 26 + 97;
        }
        return s;
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

int main()
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
}
