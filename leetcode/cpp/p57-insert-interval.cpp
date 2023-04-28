// LeetCode 57. Insert Interval.
#include "leetcode.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
    {
        auto it_begin = std::lower_bound(intervals.begin(), intervals.end(), newInterval, [](const auto& interval, const auto& value) -> bool { return interval[1] < value[0]; });
        auto it_end = std::upper_bound(it_begin, intervals.end(), newInterval, [](const auto& value, const auto& interval) -> bool { return value[1] < interval[0]; });
        if (it_begin == it_end) {
            intervals.insert(it_begin, newInterval);
            return intervals;
        }
        auto it_back = it_end - 1;
        (*it_back)[0] = std::min(newInterval[0], (*it_begin)[0]);
        (*it_back)[1] = std::max(newInterval[1], (*it_back)[1]);
        intervals.erase(it_begin, it_back);
        return intervals;
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> intervals;
        std::vector<int> newInterval;
        std::vector<std::vector<int>> exp;
    };

    const TestCase test_cases[] = {
        { {}, { 1, 5 }, { { 1, 5 } } },
        { { { 0, 1 } }, { 2, 5 }, { { 0, 1 }, { 2, 5 } } },
        { { { 2, 5 } }, { 0, 1 }, { { 0, 1 }, { 2, 5 } } },
        { { { 0, 1 } }, { 1, 5 }, { { 0, 5 } } },
        { { { 0, 2 } }, { 1, 5 }, { { 0, 5 } } },
        { { { 1, 5 } }, { 0, 2 }, { { 0, 5 } } },
        { { { 1, 5 } }, { 0, 1 }, { { 0, 5 } } },
        { { { 1, 3 }, { 6, 7 } }, { 4, 5 }, { { 1, 3 }, { 4, 5 }, { 6, 7 } } },
        { { { 1, 3 }, { 6, 7 } }, { 3, 5 }, { { 1, 5 }, { 6, 7 } } },
        { { { 1, 3 }, { 6, 7 } }, { 4, 6 }, { { 1, 3 }, { 4, 7 } } },
        { { { 1, 4 }, { 6, 7 } }, { 2, 3 }, { { 1, 4 }, { 6, 7 } } },
        { { { 1, 3 }, { 4, 7 } }, { 5, 6 }, { { 1, 3 }, { 4, 7 } } },
        { { { 1, 3 }, { 6, 9 } }, { 2, 5 }, { { 1, 5 }, { 6, 9 } } },
        { { { 1, 2 }, { 4, 5 }, { 6, 7 }, { 8, 10 }, { 12, 16 } }, { 3, 8 }, { { 1, 2 }, { 3, 10 }, { 12, 16 } } },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        auto intervals = tc.intervals;
        auto newInterval = tc.newInterval;
        const auto act = solution.insert(intervals, newInterval);
        if (tc.exp != act) {
            std::cerr << "Fail. intervals: "
                      << leetcode::to_string(tc.intervals)
                      << ", newInterval: "
                      << leetcode::to_string(tc.newInterval)
                      << ", exp: "
                      << leetcode::to_string(tc.exp)
                      << ", act: "
                      << leetcode::to_string(act)
                      << "\n";
        }
    }
    return 0;
}