// LeetCode 51. N-Queens.
#include <array>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using XVal = uint8_t;
using YVal = uint8_t;
using FlagType = uint16_t;
using Answer = std::vector<std::vector<std::string>>;
using Rows = std::array<XVal, 10>;

std::string to_string(const Answer& ans)
{
    std::ostringstream oss;
    for (const auto& grid : ans) {
        for (const auto& row : grid) {
            oss << row << "\n";
        }
        oss << "\n";
    }
    return oss.str();
}

static std::vector<std::string> to_vec_str(const Rows& rows, YVal N)
{
    std::vector<std::string> vec_str;
    for (size_t i = 0; i < N; ++i) {
        std::string s(N, '.');
        assert(rows[i] < s.size() && " bad row index");
        s[rows[i]] = 'Q';
        vec_str.push_back(s);
    }
    return vec_str;
}
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
    Answer solveNQueens(int n)
    {
        assert(1 <= n && n <= 9);
        Answer ans;
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
                        ans.push_back(to_vec_str(rows, N));
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

        return ans;
    }
};

int main()
{
    struct TestCase {
        int n;
        Answer exp;
    };
    const TestCase test_cases[] {
        { 1, { { "Q" } } },
        { 2, {} },
        { 3, {} },
        { 4, { { ".Q..", "...Q", "Q...", "..Q." }, { "..Q.", "Q...", "...Q", ".Q.." } } },
        { 5, {
                 { "Q....", "..Q..", "....Q", ".Q...", "...Q." },
                 { "Q....", "...Q.", ".Q...", "....Q", "..Q.." },
                 { ".Q...", "...Q.", "Q....", "..Q..", "....Q" },
                 { ".Q...", "....Q", "..Q..", "Q....", "...Q." },
                 { "..Q..", "Q....", "...Q.", ".Q...", "....Q" },
                 { "..Q..", "....Q", ".Q...", "...Q.", "Q...." },
                 { "...Q.", "Q....", "..Q..", "....Q", ".Q..." },
                 { "...Q.", ".Q...", "....Q", "..Q..", "Q...." },
                 { "....Q", ".Q...", "...Q.", "Q....", "..Q.." },
                 { "....Q", "..Q..", "Q....", "...Q.", ".Q..." },
             } },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        const auto ans = solution.solveNQueens(tc.n);
        if (tc.exp != ans) {
            std::cerr << "Fail, n: " << tc.n
                      << "\nexp: \n"
                      << to_string(tc.exp)
                      << "\nans: \n"
                      << to_string(ans);
        }
    }
    return 0;
}