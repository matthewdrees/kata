// LeetCode 49. Group anagrams.
#include "leetcode.hpp"

#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<vector>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> um;
        for (const auto &s : strs) {
            auto s_sorted = s;
            std::ranges::sort(s_sorted);
            um[s_sorted].push_back(s);
        }
        std::vector<std::vector<std::string>> groups;
        for (auto it = um.begin(); it != um.end(); ++it) {
            groups.push_back(it->second);
        }
        return groups;
    }
};

int main() {
    struct TestCase {
        std::vector<std::string> strs;
        std::vector<std::vector<std::string>> exp;
    };

    TestCase test_cases[] = {
        {{"eat","tea","tan","ate","nat","bat"}, {{"bat"},{"tan","nat"},{"eat","tea","ate"}}},
        {{""}, {{""}}},
        {{"a"}, {{"a"}}},
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.groupAnagrams(tc.strs);
        if (tc.exp != act) {
            std::cerr << "fail. strs: " << leetcode::to_string(tc.strs)
                << ", exp: " << leetcode::to_string(tc.exp)
                << ", act: " << leetcode::to_string(act)
                << "\n";
        }
    }
    return 0;
}
