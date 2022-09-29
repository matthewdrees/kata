// LeetCode 38. Count and Say.
#include <algorithm>
#include <iostream>

std::string say(const std::string& s)
{
    std::string ret;
    ret.reserve(s.size() * 2);
    auto it1 = s.begin();
    do {
        auto it2 = std::find_if_not(it1, s.end(), [=](const char c) { return c == *it1; });
        ret += static_cast<char>('0' + (it2 - it1));
        ret += *it1;
        it1 = it2;
    } while (it1 != s.end());
    return ret;
}

class Solution {
public:
    std::string countAndSay(int n)
    {
        std::string s = "1";
        for (int i = 1; i < n; ++i) {
            s = say(s);
        }
        return s;
    }
};

int main()
{
    struct TestCase {
        int n;
        std::string exp;
    };
    TestCase test_cases[] = {
        { 1, "1" },
        { 2, "11" },
        { 3, "21" },
        { 4, "1211" },
        { 5, "111221" },
        { 6, "312211" },
        { 7, "13112221" },
        { 8, "1113213211" },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.countAndSay(tc.n);
        if (tc.exp != act) {
            std::cout << "FAIL: n: " << tc.n
                      << ", exp: " << tc.exp
                      << ", act: " << act << "\n";
        }
    }
    return 0;
}