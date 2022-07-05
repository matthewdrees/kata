// LeetCode 1762. Buildings With an Ocean View.
#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> findBuildings(const std::vector<int>& heights)
    {
        int cur_highest = 0;
        std::vector<int> indexes;
        for (size_t i = heights.size(); i-- > 0;) {
            if (heights[i] > cur_highest) {
                indexes.push_back(static_cast<int>(i));
                cur_highest = heights[i];
            }
        }
        std::reverse(indexes.begin(), indexes.end());
        return indexes;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> heights;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { {}, {} },
        { { 4, 2, 3, 1 }, { 0, 2, 3 } },
        { { 4, 3, 2, 1 }, { 0, 1, 2, 3 } },
        { { 1, 2, 3, 4 }, { 3 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.findBuildings(tc.heights);
        if (tc.exp != ans) {
            std::cout << "FAIL. "
                      << "(heights.size()): " << tc.heights.size() << ")"
                      << ", exp size: " << tc.exp.size()
                      << ", ans size: " << ans.size() << "\n";
        }
    }
    return 0;
}