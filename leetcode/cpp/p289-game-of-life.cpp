// LeetCode 289. Game of Life.
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
    void gameOfLife(std::vector<std::vector<int>>& board)
    {
        const auto y_size = static_cast<int>(board.size());
        if (y_size == 0) {
            return;
        }
        const auto x_size = static_cast<int>(board[0].size());
        const auto b = board; // Copy of board.
        constexpr std::pair<int, int> directions[] = {
            { -1, -1 },
            { 0, -1 },
            { 1, -1 },
            { -1, 0 },
            { 1, 0 },
            { -1, 1 },
            { 0, 1 },
            { 1, 1 },
        };
        for (int y = 0; y < y_size; ++y) {
            for (int x = 0; x < x_size; ++x) {
                int num_neighbors = 0;
                for (const auto& d : directions) {
                    const int y_ = y + d.second;
                    if (y_ >= 0 and y_ < y_size) {
                        const int x_ = x + d.first;
                        if (x_ >= 0 and x_ < x_size) {
                            num_neighbors += b[y_][x_];
                        }
                    }
                }
                if (b[y][x] == 0) {
                    // Dead cell, if 3 neighbors bring back to life.
                    if (num_neighbors == 3) {
                        board[y][x] = 1;
                    }
                } else {
                    // Live cell, should we kill it?
                    if (num_neighbors < 2 || num_neighbors > 3) {
                        board[y][x] = 0;
                    }
                }
            }
        }
    }
};

static std::string toString(std::vector<std::vector<int>> board)
{
    std::ostringstream oss;
    for (const auto& row : board) {
        for (const auto& c : row) {
            oss << c << ',';
        }
        oss << '\n';
    }
    return oss.str();
}

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> exp;
    };
    const TestCase testCases[] = {
        { { { 0, 1, 0 },
              { 0, 0, 1 },
              { 1, 1, 1 },
              { 0, 0, 0 } },
            { { 0, 0, 0 },
                { 1, 0, 1 },
                { 0, 1, 1 },
                { 0, 1, 0 } } },
        { { { 1, 1 },
              { 1, 0 } },
            { { 1, 1 },
                { 1, 1 } } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        auto ans = tc.board; // Copy because call modifies in place.
        s.gameOfLife(ans);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(board: " << toString(tc.board) << ")"
                      << ", exp: " << toString(tc.exp)
                      << ", ans: " << toString(ans) << "\n";
        }
    }
    return 0;
}
