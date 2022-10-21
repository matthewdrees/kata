// LeetCode 30. Combination Sum.
#include <algorithm>
#include <iostream>
#include <vector>

#include "leetcode.hpp"

class Solution {
    std::vector<std::vector<int>> _combinations;
    int _target;
    void recurse(const std::vector<int>& candidates, size_t index, int tot, std::vector<int>& partials)
    {
        if (tot == _target) {
            _combinations.push_back(partials);
            return;
        }
        if (index >= candidates.size()) {
            return;
        }
        const int remainder = _target - tot;
        const int n = candidates[index];
        if (remainder < n) {
            return;
        }
        const size_t n_count = static_cast<size_t>(remainder / n);
        partials.insert(partials.end(), n_count, n);
        int m = n * n_count;
        while (true) {
            recurse(candidates, index + 1, tot + m, partials);
            if (m == 0) {
                break;
            }
            partials.pop_back();
            m -= n;
        }
    }

public:
    std::vector<std::vector<int>>
    combinationSum(std::vector<int>& candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end());
        candidates.erase(std::find_if(candidates.begin(), candidates.end(), [=](const int i) { return i > target; }), candidates.end());
        _combinations.clear();
        _target = target;
        std::vector<int> partials;
        recurse(candidates, 0, 0, partials);
        return _combinations;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> candidates;
        int target;
        std::vector<std::vector<int>> exp;
    };

    const TestCase test_cases[] = {
        { { 2, 3, 6, 7, 8 }, 7, { { 2, 2, 3 }, { 7 } } },
        { { 2, 3, 5 }, 8, { { 2, 2, 2, 2 }, { 2, 3, 3 }, { 3, 5 } } },
        { { 2 }, 1, {} },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        auto candidates_copy = tc.candidates;
        const auto act = solution.combinationSum(candidates_copy, tc.target);
        if (tc.exp != act) {
            std::cerr << "Fail. candidates: " << leetcode::to_string(tc.candidates)
                      << ", target: " << tc.target
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
    return 0;
}