#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "leetcode.hpp"

using namespace std;

class Solution {
public:
    bool uniqueOccurrences(const std::vector<int>& arr)
    {
        std::unordered_map<int, int> um;
        for (const auto n : arr) {
            auto it = um.find(n);
            if (it != um.end()) {
                ++it->second;
            } else {
                um.insert({ n, 0 });
            }
        }
        std::unordered_set<int> us;
        for (const auto& p : um) {
            const auto it = us.find(p.second);
            if (it != us.end()) {
                return false;
            }
            us.insert(p.second);
        }
        return true;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::vector<int> arr;
        bool exp;
    };
    const TestCase testCases[] = {
        { { 1, 2, 2, 1, 1, 3 }, true },
        { { 1, 2 }, false },
        { { -3, 0, 1, -3, 1, 1, 1, -3, 10, 0 }, true },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.uniqueOccurrences(tc.arr);
        if (tc.exp != ans) {
            cout << "FAIL. num: " << leetcode::to_string(tc.arr)
                 << ", exp: " << tc.exp
                 << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
