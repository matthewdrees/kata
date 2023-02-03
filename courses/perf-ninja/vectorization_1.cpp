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

using transposed_sequence_t = std::array<std::array<uint8_t, sequence_count_v>, sequence_size_v>;

result_t compute_alignment(std::vector<sequence_t> const &, std::vector<sequence_t> const &);

// Clang-12 compiler generates branches for std::max, which are often mispredicted
// in this benchmark. That's the reason we provide branchless version of max function.
template <typename T>
inline T max(T a, T b)
{
    return a - ((a - b) & (a - b) >> 31);
}

using score_t = result_t;
using column_t = std::array<score_t, sequence_size_v>;

// std::string to_string(const column_t &c)
// {
//     std::string s;
//     for (const auto n : c)
//     {
//         s += std::to_string(n) + ", ";
//     }
//     return s;
// }

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

transposed_sequence_t transpose(const std::vector<sequence_t> &v)
{
    assert(v.size() == sequence_count_v);
    transposed_sequence_t t;
    for (size_t y = 0; y < sequence_count_v; ++y)
    {
        const sequence_t &s_t = v[y];
        for (size_t x = 0; x < sequence_size_v; ++x)
        {
            t[x][y] = s_t[x];
        }
    }
    return t;
}

// The alignment algorithm which computes the alignment of the given sequence
// pairs.
result_t compute_alignment(std::vector<sequence_t> const &sequences1,
                           std::vector<sequence_t> const &sequences2)
{
    result_t result{};

    const auto t_sequences1 = transpose(sequences1);
    const auto t_sequences2 = transpose(sequences2);

    /*
     * Initialise score values.
     */
    score_t gap_open;
    gap_open.fill(-11);
    score_t gap_extension;
    gap_extension.fill(-1);
    score_t match;
    match.fill(6);
    score_t mismatch;
    mismatch.fill(-4);

    /*
     * Setup the matrix.
     * Note we can compute the entire matrix with just one column in memory,
     * since we are only interested in the last value of the last column in the
     * score matrix.
     */
    column_t score_column{};
    column_t horizontal_gap_column{};
    score_t last_vertical_gap = gap_open;

    for (size_t i = 0; i < score_column.size(); ++i)
    {
        for (size_t k = 0; k < sequence_count_v; ++k)
        {
            score_column[i][k] = last_vertical_gap[k];
            horizontal_gap_column[i][k] = last_vertical_gap[k] + gap_open[k];
            last_vertical_gap[k] += gap_extension[k];
        }
    }

    score_t last_score{};
    score_t last_horizontal_gap = gap_open;
    /*
     * Compute the main recursion to fill the matrix.
     */
    for (unsigned col = 0; col < t_sequences2.size(); ++col)
    {
        score_t last_diagonal_score =
            last_score; // Cache last diagonal score to compute this cell.

        for (size_t k = 0; k < sequence_count_v; ++k)
        {
            last_score[k] = last_horizontal_gap[k];
            last_vertical_gap[k] = last_horizontal_gap[k] + gap_open[k];
            last_horizontal_gap[k] += gap_extension[k];
        }

        for (unsigned row = 0; row < t_sequences1.size(); ++row)
        {
            // Compute next score from diagonal direction with match/mismatch.
            score_t best_cell_score = last_diagonal_score;
            for (size_t k = 0; k < sequence_count_v; ++k)
            {
                best_cell_score[k] += (t_sequences1[row][k] == t_sequences2[col][k] ? match[k] : mismatch[k]);
            }
            for (size_t k = 0; k < sequence_count_v; ++k)
            {
                // Determine best score from diagonal, vertical, or horizontal
                // direction.
                best_cell_score[k] = max(best_cell_score[k], last_vertical_gap[k]);
                best_cell_score[k] = max(best_cell_score[k], horizontal_gap_column[row][k]);
                // Cache next diagonal value and store optimum in score_column.
                last_diagonal_score[k] = score_column[row][k];
                score_column[row][k] = best_cell_score[k];
                // Compute the next values for vertical and horizontal gap.
                best_cell_score[k] += gap_open[k];
                last_vertical_gap[k] += gap_extension[k];
                horizontal_gap_column[row][k] += gap_extension[k];
                // Store optimum between gap open and gap extension.
                last_vertical_gap[k] = max(last_vertical_gap[k], best_cell_score[k]);
                horizontal_gap_column[row][k] =
                    max(horizontal_gap_column[row][k], best_cell_score[k]);
                // std::cout << "sq: " << sequence_idx
                //           << ", c: " << col
                //           << ", r: " << row
                //           << ", s1[" << row - 1 << "]: " << static_cast<uint16_t>(t_sequences1[row])
                //           << ", s2[" << row - 1 << "]: " << static_cast<uint16_t>(t_sequences2[row])
                //           << ", s2[" << col - 1 << "]: " << static_cast<uint16_t>(t_sequences2[col])
                //           << ", bcs: " << best_cell_score
                //           << ", lds: " << last_diagonal_score
                //           << ", lvg: " << last_vertical_gap
                //           << ", score: " << to_string(score_column)
                //           << ", hgc: " << to_string(horizontal_gap_column)
                //           << "\n";
            }
        }
    }

    // std::cout << "score_column: " << to_string(score_column) << "\n";
    // std::cout << "horizontal_gap_column: " << to_string(horizontal_gap_column) << "\n";

    // Report the best score.
    for (size_t k = 0; k < sequence_count_v; ++k)
    {
        result[k] = score_column.back()[k];
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
        {{{0, 1, 1, 0}, {0, 2, 1, 1}, {3, 1, 2, 3}},
         {{0, 0, 0, 3}, {2, 0, 0, 3}, {0, 0, 1, 3}},
         {-6, -16, -5}},
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