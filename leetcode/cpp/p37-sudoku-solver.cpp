// LeetCode 37. Sudoku Solver.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
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

using Board = std::vector<std::vector<char>>;

//                               123456789
const uint16_t ALL_NINE_BITS = 0b1111111110;

struct BoardNums {
    // Bit shifted numbers used by current board.
    uint16_t row_nums[9];
    uint16_t col_nums[9];
    uint16_t square_nums[9];

    BoardNums()
    {
        std::fill(std::begin(row_nums), std::end(row_nums), ALL_NINE_BITS);
        std::fill(std::begin(col_nums), std::end(col_nums), ALL_NINE_BITS);
        std::fill(std::begin(square_nums), std::end(square_nums), ALL_NINE_BITS);
    }
};

BoardNums build_board_nums(const Board& board)
{
    BoardNums board_nums;
    uint8_t pos = 0;
    for (const auto& row : board) {
        for (const auto c : row) {
            if (c != '.') {
                assert(c >= '1' && c <= '9');
                const uint16_t num = 1 << (c - '0');
                board_nums.row_nums[get_row_nums_index(pos)] &= ~num;
                board_nums.col_nums[get_col_nums_index(pos)] &= ~num;
                board_nums.square_nums[get_square_nums_index(pos)] &= ~num;
            }
            ++pos;
        }
    }
    return board_nums;
}

struct EmptyCell {
    uint8_t pos = 0; // Cell position from original board.

    // Pre-calculated indexes for row/col/square.
    uint8_t row_nums_index = 0;
    uint8_t col_nums_index = 0;
    uint8_t square_nums_index = 0;

    // Bit-shifted current num (1 << x)
    uint16_t num = 1;

    // Possible numbers for this cell (bit-shifted).
    uint16_t possible_nums = 0;

    void set_possible_nums(const BoardNums& board_nums)
    {
        possible_nums = board_nums.row_nums[row_nums_index] & board_nums.col_nums[col_nums_index] & board_nums.square_nums[square_nums_index];
    }

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

std::vector<EmptyCell> build_empty_cells(const Board& board)
{
    std::vector<EmptyCell> empty_cells;
    uint8_t pos = 0;
    for (const auto& row : board) {
        for (const auto c : row) {
            if (c == '.') {
                empty_cells.push_back(build_empty_cell(pos));
            }
            ++pos;
        }
    }
    return empty_cells;
}

char num_to_c(uint16_t num)
{
    for (int i = 1; i < 10; ++i) {
        if ((1 << i) == num) {
            return '0' + i;
        }
    }
    return '.';
}

void solve_empty_cells(BoardNums board_nums, std::vector<EmptyCell>& empty_cells)
{
    auto empty_cell = empty_cells.begin();
    while (true) {
        if (empty_cell == empty_cells.end()) {
            break;
        }
        if (empty_cell->num == 1) {
            empty_cell->set_possible_nums(board_nums);
            if (empty_cell->possible_nums == 0) {
                empty_cell->num = (1 << 10);
            }
        } else {
            board_nums.row_nums[empty_cell->row_nums_index] |= empty_cell->num;
            board_nums.col_nums[empty_cell->col_nums_index] |= empty_cell->num;
            board_nums.square_nums[empty_cell->square_nums_index] |= empty_cell->num;
        }
        for (empty_cell->num <<= 1; empty_cell->num < (1 << 10); empty_cell->num <<= 1) {
            if (empty_cell->num & empty_cell->possible_nums) {
                break;
            }
        }
        if (empty_cell->num < (1 << 10)) {
            board_nums.row_nums[empty_cell->row_nums_index] &= ~empty_cell->num;
            board_nums.col_nums[empty_cell->col_nums_index] &= ~empty_cell->num;
            board_nums.square_nums[empty_cell->square_nums_index] &= ~empty_cell->num;
            ++empty_cell;
            continue;
        }
        empty_cell->num = 1;
        if (empty_cell == empty_cells.begin()) {
            break;
        }
        --empty_cell;
    }
}

void fill_empty_board_cells(const std::vector<EmptyCell>& empty_cells, Board& board)
{
    for (const auto& empty_cell : empty_cells) {
        size_t x = empty_cell.pos % 9;
        size_t y = empty_cell.pos / 9;
        board[y][x] = num_to_c(empty_cell.num);
    }
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
    const TestCase testCases[] = {
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
                { '3', '4', '5', '2', '8', '6', '1', '7', '9' } } },
        { { { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.', '.', '.', '.', '.' } },
            { { '1', '2', '3', '4', '5', '6', '7', '8', '9' },
                { '4', '5', '6', '7', '8', '9', '1', '2', '3' },
                { '7', '8', '9', '1', '2', '3', '4', '5', '6' },
                { '2', '1', '4', '3', '6', '5', '8', '9', '7' },
                { '3', '6', '5', '8', '9', '7', '2', '1', '4' },
                { '8', '9', '7', '2', '1', '4', '3', '6', '5' },
                { '5', '3', '1', '6', '4', '2', '9', '7', '8' },
                { '6', '4', '2', '9', '7', '8', '5', '3', '1' },
                { '9', '7', '8', '5', '3', '1', '6', '4', '2' } } },
    };

    Solution s;
    for (const auto& tc : testCases) {
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
