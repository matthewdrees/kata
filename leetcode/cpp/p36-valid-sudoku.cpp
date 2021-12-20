// LeetCode 36. Valid Sudoku.
#include <iostream>
#include <unordered_set>
#include <vector>

#include "leetcode.hpp"

class Solution {
public:
    bool isValidSudoku(const std::vector<std::vector<char>>& board)
    {
        // Rows
        for (const auto& row : board) {
            std::unordered_set<char> row_vals;
            for (const auto n : row) {
                if (n != '.') {
                    if (row_vals.find(n) != row_vals.end()) {
                        return false;
                    }
                    row_vals.insert(n);
                }
            }
        }
        // Columns
        {
            std::unordered_set<char> col_vals[9] = {};
            for (const auto& row : board) {
                for (size_t x = 0; x < 9; ++x) {
                    const auto n = row[x];
                    if (n != '.') {
                        if (col_vals[x].find(n) != col_vals[x].end()) {
                            return false;
                        }
                        col_vals[x].insert(n);
                    }
                }
            }
        }
        // Squares
        {
            std::unordered_set<char> sq_vals[9] = {};
            for (size_t y = 0; y < 9; ++y) {
                const auto& row = board[y];
                for (size_t x = 0; x < 9; ++x) {
                    const auto n = row[x];
                    const size_t sq = (y / 3) * 3 + x / 3;
                    if (n != '.') {
                        if (sq_vals[sq].find(n) != sq_vals[sq].end()) {
                            return false;
                        }
                        sq_vals[sq].insert(n);
                    }
                }
            }
        }
        return true;
    }
};

int main()
{
    struct TestCase {
        std::vector<std::vector<char>> board;
        bool exp;
    };
    const TestCase tcs[] = {
        { { { '5', '3', '.', '.', '7', '.', '.', '.', '.' }, { '6', '.', '.', '1', '9', '5', '.', '.', '.' }, { '.', '9', '8', '.', '.', '.', '.', '6', '.' }, { '8', '.', '.', '.', '6', '.', '.', '.', '3' }, { '4', '.', '.', '8', '.', '3', '.', '.', '1' }, { '7', '.', '.', '.', '2', '.', '.', '.', '6' }, { '.', '6', '.', '.', '.', '.', '2', '8', '.' }, { '.', '.', '.', '4', '1', '9', '.', '.', '5' }, { '.', '.', '.', '.', '8', '.', '.', '7', '9' } },
            true },
        { { { '8', '3', '.', '.', '7', '.', '.', '.', '.' }, { '6', '.', '.', '1', '9', '5', '.', '.', '.' }, { '.', '9', '8', '.', '.', '.', '.', '6', '.' }, { '8', '.', '.', '.', '6', '.', '.', '.', '3' }, { '4', '.', '.', '8', '.', '3', '.', '.', '1' }, { '7', '.', '.', '.', '2', '.', '.', '.', '6' }, { '.', '6', '.', '.', '.', '.', '2', '8', '.' }, { '.', '.', '.', '4', '1', '9', '.', '.', '5' }, { '.', '.', '.', '.', '8', '.', '.', '7', '9' } },
            false }
    };
    Solution solution;
    for (const auto& tc : tcs) {
        const auto act = solution.isValidSudoku(tc.board);
        if (tc.exp != act) {
            std::cerr << "Fail. board: " << leetcode::to_string(tc.board)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
    return 0;
}
