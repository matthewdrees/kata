// LeetCode 31. Next permutation.
#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

class Solution {
public:
    void nextPermutation(std::vector<int>& nums)
    {
        if (nums.size() <= 1) {
            return;
        }

        {
            // Half of all permutations are swapping the last 2 elements.
            // Optimize that case.
            const size_t i1 = nums.size() - 2;
            const size_t i2 = nums.size() - 1;
            if (nums[i1] < nums[i2]) {
                std::swap(nums[i1], nums[i2]);
                return;
            }
        }

        for (size_t i = nums.size() - 2; i-- > 0;) {
            const auto n1 = nums[i];
            const auto n2 = nums[i + 1];
            if (n1 < n2) {
                auto j = nums.size();
                while (j-- > i + 1) {
                    if (n1 < nums[j]) {
                        break;
                    }
                }
                std::swap(nums[i], nums[j]);
                std::reverse(nums.begin() + i + 1, nums.end());
                return;
            }
        }
        std::reverse(nums.begin(), nums.end());
    }
};

static std::string toString(std::vector<int> nums)
{
    std::ostringstream oss;
    for (const auto& n : nums) {
        oss << n << ',';
    }
    return oss.str();
}

const size_t MAX_SIZE = 16;
static void BM_mine(benchmark::State& state)
{
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        v.push_back(i);
    }
    Solution solution;
    for (auto _ : state) {
        solution.nextPermutation(v);
    }
}
BENCHMARK(BM_mine)->Range(0, MAX_SIZE);

static void BM_stl(benchmark::State& state)
{
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        v.push_back(i);
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(std::next_permutation(v.begin(), v.end()));
    }
}
BENCHMARK(BM_stl)->Range(0, MAX_SIZE);

//BENCHMARK_MAIN();

int main()
{
    struct TestCase {
        std::vector<int> nums;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { {}, {} },
        { { 0 }, { 0 } },
        { { 0, 1 }, { 1, 0 } },
        { { 1, 0 }, { 0, 1 } },

        { { 1, 2, 3 }, { 1, 3, 2 } },
        { { 1, 3, 2 }, { 2, 1, 3 } },
        { { 2, 1, 3 }, { 2, 3, 1 } },
        { { 2, 3, 1 }, { 3, 1, 2 } },
        { { 3, 1, 2 }, { 3, 2, 1 } },
        { { 3, 2, 1 }, { 1, 2, 3 } },

        { { 1, 2, 2 }, { 2, 1, 2 } },
        { { 2, 1, 2 }, { 2, 2, 1 } },
        { { 2, 2, 1 }, { 1, 2, 2 } },

        { { 1, 2, 3, 4 }, { 1, 2, 4, 3 } },
        { { 1, 2, 4, 3 }, { 1, 3, 2, 4 } },
        { { 1, 3, 2, 4 }, { 1, 3, 4, 2 } },
        { { 1, 3, 4, 2 }, { 1, 4, 2, 3 } },
        { { 1, 4, 2, 3 }, { 1, 4, 3, 2 } },
        { { 1, 4, 3, 2 }, { 2, 1, 3, 4 } },

        { { 2, 1, 3, 4 }, { 2, 1, 4, 3 } },
        { { 2, 1, 4, 3 }, { 2, 3, 1, 4 } },
        { { 2, 3, 1, 4 }, { 2, 3, 4, 1 } },
        { { 2, 3, 4, 1 }, { 2, 4, 1, 3 } },
        { { 2, 4, 1, 3 }, { 2, 4, 3, 1 } },
        { { 2, 4, 3, 1 }, { 3, 1, 2, 4 } },

        { { 3, 1, 2, 4 }, { 3, 1, 4, 2 } },
        { { 3, 1, 4, 2 }, { 3, 2, 1, 4 } },
        { { 3, 2, 1, 4 }, { 3, 2, 4, 1 } },
        { { 3, 2, 4, 1 }, { 3, 4, 1, 2 } },
        { { 3, 4, 1, 2 }, { 3, 4, 2, 1 } },
        { { 3, 4, 2, 1 }, { 4, 1, 2, 3 } },

        { { 4, 1, 2, 3 }, { 4, 1, 3, 2 } },
        { { 4, 1, 3, 2 }, { 4, 2, 1, 3 } },
        { { 4, 2, 1, 3 }, { 4, 2, 3, 1 } },
        { { 4, 2, 3, 1 }, { 4, 3, 1, 2 } },
        { { 4, 3, 1, 2 }, { 4, 3, 2, 1 } },
        { { 4, 3, 2, 1 }, { 1, 2, 3, 4 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        auto ans = tc.nums; // Copy because call modifies in place.
        s.nextPermutation(ans);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(nums: " << toString(tc.nums) << ")"
                      << ", exp: " << toString(tc.exp)
                      << ", ans: " << toString(ans) << "\n";
        }
    }
    return 0;
}
