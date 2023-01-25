// perf-ninja vectorization_1 solution.

#include <cassert>
#include <type_traits>

#include <array>   // std::array
#include <cstddef> // size_t
#include <cstdint> // fixed width types
#include <iostream>
#include <utility> // std::pair
#include <vector>  // std::vector

inline constexpr size_t sequence_size_v = 4;  // The length of the generated sequences.
inline constexpr size_t sequence_count_v = 3; // The number of sequences to generate for both sequence collections.

using sequence_t = std::array<uint8_t, sequence_size_v>;
using result_t = std::array<int16_t, sequence_count_v>;

result_t compute_alignment(std::vector<sequence_t> const &, std::vector<sequence_t> const &);
std::pair<std::vector<sequence_t>, std::vector<sequence_t>> init();

// Clang-12 compiler generates branches for std::max, which are often mispredicted
// in this benchmark. That's the reason we provide branchless version of max function.
template <typename T>
inline T max(T a, T b)
{
    return a - ((a - b) & (a - b) >> 31);
}

using score_t = int16_t;
using column_t = std::array<score_t, sequence_size_v + 1>;

std::string to_string(const column_t &c)
{
    std::string s;
    for (const auto n : c)
    {
        s += std::to_string(n) + ", ";
    }
    return s;
}

std::string to_string(const sequence_t &seq)
{
    std::string s;
    for (const auto n : seq)
    {
        s += std::to_string(static_cast<uint16_t>(n)) + ", ";
    }
    return s;
}

std::string to_string(const result_t &r)
{
    std::string s;
    for (const auto n : r)
    {
        s += std::to_string(n) + ", ";
    }
    return s;
}
// The alignment algorithm which computes the alignment of the given sequence
// pairs.
result_t compute_alignment(std::vector<sequence_t> const &sequences1,
                           std::vector<sequence_t> const &sequences2)
{
    result_t result{};

    for (size_t sequence_idx = 0; sequence_idx < sequences1.size();
         ++sequence_idx)
    {

        sequence_t const &sequence1 = sequences1[sequence_idx];
        sequence_t const &sequence2 = sequences2[sequence_idx];

        /*
         * Initialise score values.
         */
        score_t gap_open{-11};
        score_t gap_extension{-1};
        score_t match{6};
        score_t mismatch{-4};

        /*
         * Setup the matrix.
         * Note we can compute the entire matrix with just one column in memory,
         * since we are only interested in the last value of the last column in the
         * score matrix.
         */
        column_t score_column{};
        column_t horizontal_gap_column{};
        score_t last_vertical_gap{};

        /*
         * Initialise the first column of the matrix.
         */
        horizontal_gap_column[0] = gap_open;
        last_vertical_gap = gap_open;

        for (size_t i = 1; i < score_column.size(); ++i)
        {
            score_column[i] = last_vertical_gap;
            horizontal_gap_column[i] = last_vertical_gap + gap_open;
            last_vertical_gap += gap_extension;
        }
        std::cout << "score_column: " << to_string(score_column) << "\n";
        std::cout << "horizontal_gap_column: " << to_string(horizontal_gap_column) << "\n";

        /*
         * Compute the main recursion to fill the matrix.
         */
        for (unsigned col = 1; col <= sequence2.size(); ++col)
        {
            score_t last_diagonal_score =
                score_column[0]; // Cache last diagonal score to compute this cell.
            score_column[0] = horizontal_gap_column[0];
            score_t _last_vertical_gap = horizontal_gap_column[0] + gap_open;
            horizontal_gap_column[0] += gap_extension;

            for (unsigned row = 1; row <= sequence1.size(); ++row)
            {
                // Compute next score from diagonal direction with match/mismatch.
                score_t best_cell_score =
                    last_diagonal_score +
                    (sequence1[row - 1] == sequence2[col - 1] ? match : mismatch);
                // Determine best score from diagonal, vertical, or horizontal
                // direction.
                best_cell_score = max(best_cell_score, _last_vertical_gap);
                best_cell_score = max(best_cell_score, horizontal_gap_column[row]);
                // Cache next diagonal value and store optimum in score_column.
                last_diagonal_score = score_column[row];
                score_column[row] = best_cell_score;
                // Compute the next values for vertical and horizontal gap.
                best_cell_score += gap_open;
                _last_vertical_gap += gap_extension;
                horizontal_gap_column[row] += gap_extension;
                // Store optimum between gap open and gap extension.
                _last_vertical_gap = max(_last_vertical_gap, best_cell_score);
                horizontal_gap_column[row] =
                    max(horizontal_gap_column[row], best_cell_score);
                std::cout << "sq: " << sequence_idx
                          << ", c: " << col
                          << ", r: " << row
                          << ", s1[" << row - 1 << "]: " << static_cast<uint16_t>(sequence1[row - 1])
                          << ", s2[" << row - 1 << "]: " << static_cast<uint16_t>(sequence2[row - 1])
                          << ", s2[" << col - 1 << "]: " << static_cast<uint16_t>(sequence2[col - 1])
                          << ", bcs: " << best_cell_score
                          << ", lds: " << last_diagonal_score
                          << ", lvg: " << _last_vertical_gap
                          << ", score: " << to_string(score_column)
                          << ", hgc: " << to_string(horizontal_gap_column)
                          << "\n";
            }
        }

        std::cout << "score_column: " << to_string(score_column) << "\n";
        std::cout << "horizontal_gap_column: " << to_string(horizontal_gap_column) << "\n";
        // Report the best score.
        result[sequence_idx] = score_column.back();
    }

    return result;
}

int main()
{
    struct TestCase
    {
        std::vector<sequence_t> sequence1;
        std::vector<sequence_t> sequence2;
        result_t exp;
    };
    const TestCase test_cases[] = {
        {{{1, 2, 4, 3}, {3, 1, 0, 2}, {2, 3, 1, 2}},
         {{2, 2, 3, 4}, {3, 0, 1, 2}, {2, 1, 1, 2}},
         {-6, 4, 14}},
        // {{{0, 1, 1, 0}, {0, 2, 1, 1}, {3, 1, 2, 3}},
        //  {{0, 0, 0, 3}, {2, 0, 0, 3}, {0, 0, 1, 3}},
        //  {-6, -16, -5}},
    };
    for (const auto &tc : test_cases)
    {
        const auto act = compute_alignment(tc.sequence1, tc.sequence2);
        if (tc.exp != act)
        {
            std::cerr << "Fail, exp: { " << to_string(tc.exp)
                      << ", act: " << to_string(act)
                      << "\n";
        }
    }
    return 0;
}