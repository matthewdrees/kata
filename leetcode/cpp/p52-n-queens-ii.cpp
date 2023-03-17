// LeetCode 52. N-Queens II.
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using XVal = uint8_t;
using YVal = uint8_t;
using FlagType = uint16_t;
using Rows = std::array<XVal, 10>;

static FlagType get_col_flag(XVal x)
{
    return 1 << x;
}

static FlagType get_diag1_flag(XVal x, YVal y, YVal N)
{
    return 1 << (N + y - x);
}

static FlagType get_diag2_flag(XVal x, YVal y, YVal N)
{
    return 1 << (N + y - (N - x));
}

static bool is_flag_set(FlagType f, FlagType mask)
{
    return f & mask;
}

static void set_flag(FlagType f, FlagType& mask)
{
    mask |= f;
}

static void unset_flag(FlagType f, FlagType& mask)
{
    mask &= ~f;
}

class Solution {
public:
    int totalNQueens_cheating(int n)
    {
        // ;-)
        assert(1 <= n && n <= 9);
        constexpr std::array<int, 10> ans = {
            1,
            0,
            0,
            2,
            10,
            4,
            40,
            92,
            352,
        };
        return ans[n - 1];
    }

    int totalNQueens(int n)
    {
        assert(1 <= n && n <= 9);
        int num_distinct_solutions = 0;
        const YVal N = static_cast<YVal>(n);
        Rows rows { 0 };
        FlagType col_mask { 0 };
        FlagType diag1_mask { 0 };
        FlagType diag2_mask { 0 };
        YVal y = 0;
        while (true) {
            if (rows[y] == N) {
                if (y == 0) {
                    break;
                }
                y -= 1;
                unset_flag(get_col_flag(rows[y]), col_mask);
                unset_flag(get_diag1_flag(rows[y], y, N), diag1_mask);
                unset_flag(get_diag2_flag(rows[y], y, N), diag2_mask);
                rows[y] += 1;
            } else {
                const auto col_flag = get_col_flag(rows[y]);
                const auto diag1_flag = get_diag1_flag(rows[y], y, N);
                const auto diag2_flag = get_diag2_flag(rows[y], y, N);
                if (is_flag_set(col_flag, col_mask) || is_flag_set(diag1_flag, diag1_mask) || is_flag_set(diag2_flag, diag2_mask)) {
                    ++rows[y];
                } else {
                    if (y + 1 == N) {
                        ++num_distinct_solutions;
                        rows[y] = N;
                    } else {
                        set_flag(col_flag, col_mask);
                        set_flag(diag1_flag, diag1_mask);
                        set_flag(diag2_flag, diag2_mask);
                        y += 1;
                        rows[y] = 0;
                    }
                }
            }
        }

        return num_distinct_solutions;
    }
};

int main()
{
    struct TestCase {
        int n;
        int exp;
    };
    const TestCase test_cases[] {
        { 1, 1 },
        { 2, 0 },
        { 3, 0 },
        { 4, 2 },
        { 5, 10 },
        { 6, 4 },
        { 7, 40 },
        { 8, 92 },
        { 9, 352 },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto ans = solution.totalNQueens(tc.n);
        if (tc.exp != ans) {
            std::cerr << "Fail, n: " << tc.n
                      << "exp: " << tc.exp
                      << "ans: " << ans
                      << "\n";
        }
    }
    return 0;
}