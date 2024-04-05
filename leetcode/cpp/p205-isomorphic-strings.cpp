// LeetCode 205. Isomorphic Strings.
#include <cassert>
#include <iostream>
#include <unordered_map>

class Solution {
public:
    bool isIsomorphic(std::string s, std::string t)
    {
        char m1[128] = { 0 };
        char m2[128] = { 0 };
        for (size_t i = 0; i < s.size(); ++i) {
            const auto c1 = s[i];
            const auto c2 = t[i];
            assert(c1 >= 0 && c1 < 128);
            assert(c2 >= 0 && c2 < 128);
            char& c1val = m1[static_cast<size_t>(c1)];
            if (c1val != 0 && c1val != c2) {
                return false;
            }
            char& c2val = m2[static_cast<size_t>(c2)];
            if (c2val != 0 && c2val != c1) {
                return false;
            }
            c1val = c2;
            c2val = c1;
        }
        return true;
    }

    // First cut.
    bool isIsomorphic2(std::string s, std::string t)
    {
        if (s.size() != t.size()) {
            return false;
        }
        std::unordered_map<char, char> m1;
        std::unordered_map<char, char> m2;
        for (size_t i = 0; i < s.size(); ++i) {
            const char c1 = s[i];
            const char c2 = t[i];
            const auto it1 = m1.find(c1);
            if (it1 != m1.end() && it1->second != c2) {
                return false;
            }
            const auto it2 = m2.find(c2);
            if (it2 != m2.end() && it2->second != c1) {
                return false;
            }
            m1[c1] = c2;
            m2[c2] = c1;
        }
        return true;
    }
};

int main()
{
    struct TestCase {
        std::string s;
        std::string t;
        bool exp;
    };

    TestCase test_cases[] = {
        { "", "", true },
        { "egg", "add", true },
        { "foo", "bar", false },
        { "paper", "title", true },
        { "baba", "bada", false },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.isIsomorphic(tc.s, tc.t);
        if (tc.exp != act) {
            std::cerr << "fail, s: " << tc.s
                      << ", t: " << tc.t
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}
