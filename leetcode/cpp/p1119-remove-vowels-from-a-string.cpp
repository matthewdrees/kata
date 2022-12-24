// LeetCode 1119. Remove Vowels from a String.
#include <algorithm>
#include <iostream>
#include <string>

class Solution {
public:
    std::string removeVowels(const std::string& s)
    {
        std::string ret;
        std::copy_if(s.begin(), s.end(), std::back_inserter(ret),
            [](char c) { return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u'; });
        return ret;
    }
};

int main()
{
    struct TestCase {
        std::string s;
        std::string exp;
    };
    const TestCase test_cases[] = {
        { "leetcodeisacommunityforcoders", "ltcdscmmntyfrcdrs" },
        { "aeiou", "" },
        { "a", "" },
        { "b", "b" },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.removeVowels(tc.s);
        if (tc.exp != act) {
            std::cerr << "FAIL, s: " << tc.s
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}