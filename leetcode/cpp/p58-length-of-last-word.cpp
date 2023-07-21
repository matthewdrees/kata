// LeetCode 58. Length of Last Word
#include <algorithm>
#include <iostream>

class Solution {
public:
    int lengthOfLastWord(std::string s)
    {
        auto is_space = [](char c) { return c == ' '; };
        const auto it1 = std::find_if_not(s.rbegin(), s.rend(), is_space);
        const auto it2 = std::find_if(it1, s.rend(), is_space);
        return static_cast<int>(it2 - it1);
    }
};

int main()
{
    struct TestCase {
        std::string s;
        int exp;
    };

    TestCase test_cases[] = {
        { "", 0 },
        { " ", 0 },
        { "a", 1 },
        { "a ", 1 },
        { " a", 1 },
        { "Hello World", 5 },
        { "   fly me   to   the moon  ", 4 },
        { "luffy is still joyboy", 6 },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.lengthOfLastWord(tc.s);
        if (tc.exp != act) {
            std::cout << "Fail. s: '" << tc.s
                      << "', exp: " << tc.exp
                      << ", act: " << act
                      << '\n';
        }
    }
}