// LeetCode 2936. Number of Equal Number Blocks

#include "leetcode.hpp"

#include <cassert>
#include <iostream>
#include <vector>

class BigArray {
public:
    BigArray(std::vector<int> elements)
        : nums(elements)
    {
    }
    int at(long long index) { return nums[index]; }
    long long size() { return static_cast<long long>(nums.size()); }

private:
    std::vector<int> nums;
};

struct BlockCounter {
    BigArray* _bigArray = nullptr;

    BlockCounter(BigArray* bigArray)
        : _bigArray(bigArray)
    {
        assert(_bigArray != nullptr);
    }

    int count_transitions(long long first, long long last, int last_val)
    {
        int transitions = 0;
        int cur_val = _bigArray->at(first);
        for (long long i = first + 1; i <= last; ++i) {
            int tmp = _bigArray->at(i);
            if (cur_val != tmp) {
                transitions += 1;
                if (tmp == last_val) {
                    break;
                }
                cur_val = tmp;
            }
        }
        return transitions;
    }

    int chunk_and_count_transitions(long long first, long long last)
    {
        assert(first <= last);
        const int first_val = _bigArray->at(first);
        const int last_val = _bigArray->at(last);
        if (first_val == last_val) {
            return 0;
        }
        if (last - first < 16) {
            return count_transitions(first, last, last_val);
        }
        if (first + 1 == last) {
            return 1;
        }
        const long long middle = (last + first) / 2;
        return chunk_and_count_transitions(first, middle) + chunk_and_count_transitions(middle, last);
    }
};

class Solution {
public:
    int countBlocks(BigArray* nums)
    {
        assert(nums->size() > 0);
        BlockCounter bc(nums);
        return 1 + bc.chunk_and_count_transitions(0, nums->size() - 1);
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums;
        int exp;
    };
    TestCase test_cases[] = {
        { { 0 }, 1 },
        { { 0, 1 }, 2 },
        { { 3, 3, 3, 3, 3 }, 1 },
        { { 1, 1, 1, 3, 9, 9, 9, 2, 10, 10 }, 5 },
        { { 1, 2, 3, 4, 5, 6, 7 }, 7 },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        BigArray ba(tc.nums);
        const auto act = solution.countBlocks(&ba);
        if (tc.exp != act) {
            std::cerr << "fail, nums: " << leetcode::to_string(tc.nums)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}