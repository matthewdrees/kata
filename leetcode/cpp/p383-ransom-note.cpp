// LeetCode 383. Ransom Note.
#include <cassert>
#include <iostream>

static size_t c_to_index(char c)
{
    // assert(c >= 'a' && c <= 'z');
    return static_cast<size_t>(c - 'a');
}

class Solution {
public:
    bool canConstruct(std::string ransomNote, std::string magazine)
    {
        int chars[26] = { 0 };
        for (const char c : magazine) {
            ++chars[c_to_index(c)];
        }
        for (const char c : ransomNote) {
            const auto i = c_to_index(c);
            if (chars[i] == 0) {
                return false;
            }
            --chars[i];
        }
        return true;
    }
};

int main()
{
    struct TestCase {
        std::string ransomNote;
        std::string magazine;
        bool exp;
    };

    TestCase test_cases[] = {
        { "a", "b", false },
        { "aa", "ab", false },
        { "aa", "aab", true },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.canConstruct(tc.ransomNote, tc.magazine);
        if (tc.exp != act) {
            std::cerr << "fail, rn: " << tc.ransomNote
                      << ", mag: " << tc.magazine
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}
