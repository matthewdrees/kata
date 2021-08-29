// LeetCode 37. Sudoku Solver.
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

static uint8_t get_row_nums_index(uint8_t pos) { return pos / 9; }
static uint8_t get_col_nums_index(uint8_t pos) { return pos % 9; }
static uint8_t get_square_nums_index(uint8_t pos)
{
    constexpr uint8_t square_indexes[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2,
        0, 0, 0, 1, 1, 1, 2, 2, 2,
        0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 7, 7, 7, 8, 8, 8,
        6, 6, 6, 7, 7, 7, 8, 8, 8,
        6, 6, 6, 7, 7, 7, 8, 8, 8 };
    assert(pos < 81);
    return square_indexes[pos];
}

struct EmptyCell {
    uint8_t pos = 0; // Cell position from original board.

    // Pre-calculated indexes for row/col/square.
    uint8_t row_nums_index = 0;
    uint8_t col_nums_index = 0;
    uint8_t square_nums_index = 0;

    // Current bit-shifted num (x << 1)
    uint16_t num = 1;

    // Possible numbers for this cell (bit-shifted).
    uint16_t possible_nums = 0;

    EmptyCell() = default;
    EmptyCell(EmptyCell&) = default;
    EmptyCell(EmptyCell&&) = default;
    EmptyCell& operator=(EmptyCell& o) = default;
    EmptyCell& operator=(EmptyCell&& o) = default;
};

EmptyCell build_empty_cell(uint8_t pos)
{
    EmptyCell empty_cell;
    empty_cell.pos = pos;
    empty_cell.row_nums_index = get_row_nums_index(pos);
    empty_cell.col_nums_index = get_col_nums_index(pos);
    empty_cell.square_nums_index = get_square_nums_index(pos);
    empty_cell.num = 1;
    empty_cell.possible_nums = 0;
    return empty_cell;
}

using Board = std::vector<std::vector<char>>;

struct BoardNums {
    // Bit shifted numbers used by current board.
    uint16_t row_nums[9] = { 0 };
    uint16_t col_nums[9] = { 0 };
    uint16_t square_nums[9] = { 0 };
};

BoardNums build_board_nums(const Board&)
{
    BoardNums board_nums;
    // TODO: this
    return board_nums;
}

std::vector<EmptyCell> build_empty_cells(const Board& board)
{
    std::vector<EmptyCell> empty_cells;
    //TODO: this
    return empty_cells;
}

void solve_empty_cells(BoardNums board_nums, std::vector<EmptyCell>& empty_cells)
{
    //TODO: this
}

void fill_empty_board_cells(const std::vector<EmptyCell>& empty_cells, Board& board)
{
    // TODO: this
}

class Solution {
public:
    void solveSudoku(Board& board)
    {
        auto board_nums = build_board_nums(board);
        auto empty_cells = build_empty_cells(board);
        solve_empty_cells(board_nums, empty_cells);
        fill_empty_board_cells(empty_cells, board);
    }
};

static std::string toString(std::vector<std::vector<char>> board)
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

void test_sudokuSolver()
{
    struct TestCase {
        std::vector<std::vector<char>> board;
        std::vector<std::vector<char>> exp;
    };
    TestCase testCases[] = {
        { { { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
              { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
              { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
              { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
              { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
              { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
              { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
              { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
              { '.', '.', '.', '.', '8', '.', '.', '7', '9' } },
            { { '5', '3', '4', '6', '7', '8', '9', '1', '2' },
                { '6', '7', '2', '1', '9', '5', '3', '4', '8' },
                { '1', '9', '8', '3', '4', '2', '5', '6', '7' },
                { '8', '5', '9', '7', '6', '1', '4', '2', '3' },
                { '4', '2', '6', '8', '5', '3', '7', '9', '1' },
                { '7', '1', '3', '9', '2', '4', '8', '5', '6' },
                { '9', '6', '1', '5', '3', '7', '2', '8', '4' },
                { '2', '8', '7', '4', '1', '9', '6', '3', '5' },
                { '3', '4', '5', '2', '8', '6', '1', '7', '9' } } }
    };

    Solution s;
    for (auto& tc : testCases) {
        auto ans = tc.board; // Copy because call modifies in place.
        s.solveSudoku(ans);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(board: " << toString(tc.board) << ")"
                      << ", exp: " << toString(tc.exp)
                      << ", ans: " << toString(ans) << "\n";
        }
    }
}

int main()
{
    test_sudokuSolver();
    return 0;
}
