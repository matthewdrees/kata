// LeetCode 216. Combination Sum III.
#include "leetcode.hpp"

#include <cassert>
#include <iostream>
#include <vector>

class Solution {
    int _k { 0 };
    int _n { 0 };
    std::vector<int> _nums;
    std::vector<std::vector<int>> _output;
    const int MAX_K = 9;

public:
    void backtrack(int num, int total)
    {
        const auto count = static_cast<int>(_nums.size()) + 1;
        if (count == _k) {
            const auto last_num = _n - total;
            if (last_num >= num && last_num <= MAX_K) {
                _nums.push_back(last_num);
                _output.push_back(_nums);
                _nums.pop_back();
            }
            return;
        }
        if (total >= _n) {
            return;
        }
        for (int new_num = num; new_num <= MAX_K; ++new_num) {
            _nums.push_back(new_num);
            backtrack(new_num + 1, total + new_num);
            _nums.pop_back();
        }
    }
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        assert(k >= 2 && k <= MAX_K);
        assert(n >= 1 && n <= 60);
        _k = k;
        _n = n;
        _nums.clear();
        _output.clear();
        backtrack(1, 0);
        return _output;
    }
};

int main()
{
    struct TestCase {
        int k;
        int n;
        std::vector<std::vector<int>> exp;
    };

    const TestCase test_cases[] = {
        { 2, 1, {} },
        { 2, 3, { { 1, 2 } } },
        { 2, 4, { { 1, 3 } } },
        { 2, 10, { { 1, 9 }, { 2, 8 }, { 3, 7 }, { 4, 6 } } },
        { 2, 17, { { 8, 9 } } },
        { 3, 7, { { 1, 2, 4 } } },
        { 3, 9, { { 1, 2, 6 }, { 1, 3, 5 }, { 2, 3, 4 } } },
        { 4, 1, {} },
        { 9, 45, { { 1, 2, 3, 4, 5, 6, 7, 8, 9 } } },
        { 9, 46, {} },
        { 8, 36, { { 1, 2, 3, 4, 5, 6, 7, 8 } } },
        { 8, 37, { { 1, 2, 3, 4, 5, 6, 7, 9 } } },
        { 8, 38, { { 1, 2, 3, 4, 5, 6, 8, 9 } } },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.combinationSum3(tc.k, tc.n);
        if (tc.exp != act) {
            std::cerr << "Fail, k: " << tc.k
                      << ", n: " << tc.n
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
}
