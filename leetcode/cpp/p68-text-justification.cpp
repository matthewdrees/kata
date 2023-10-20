// LeetCode p68. Text Justification.

#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

std::string leftJustify(const std::vector<std::string>& words, size_t l, size_t r, size_t width)
{
    std::string line(width, ' ');
    auto it = line.begin();
    for (size_t i = l; i < r; ++i) {
        it = std::copy(words[i].begin(), words[i].end(), it);
        ++it;
    }
    return line;
}

std::string leftRightJustify(const std::vector<std::string>& words, size_t l, size_t r, size_t width)
{
    assert(r >= l);
    const size_t numWords = r - l;
    if (r - l < 2) {
        return leftJustify(words, l, r, width);
    }
    const size_t totalSpaces = width - std::accumulate(words.begin() + l, words.begin() + r, 0u, [](size_t s, const std::string& w) { return s + w.size(); });
    const size_t minSpacesBetweenWords = totalSpaces / (numWords - 1);
    size_t remainderSpacesBetweenWords = totalSpaces % (numWords - 1);

    std::string line(width, ' ');
    auto it = line.begin();
    for (size_t i = l; i < r; ++i) {
        it = std::copy(words[i].begin(), words[i].end(), it);
        it += minSpacesBetweenWords;
        if (remainderSpacesBetweenWords > 0) {
            ++it;
            --remainderSpacesBetweenWords;
        }
    }
    return line;
}

class Solution {
public:
    std::vector<std::string> fullJustify(const std::vector<std::string>& words, int maxWidth)
    {
        const size_t width = maxWidth;
        std::vector<std::string> output;
        size_t l = 0;
        size_t lineLength = 0;
        for (size_t r = 0; r < words.size(); ++r) {
            const auto& word = words[r];
            if (lineLength + word.size() > width) {
                output.push_back(leftRightJustify(words, l, r, width));
                l = r;
                lineLength = 0;
            }
            lineLength += word.size() + 1;
        }
        if (l != words.size()) {
            output.push_back(leftJustify(words, l, words.size(), width));
        }
        return output;
    }
};

void test_leftJustify()
{
    struct TestCase {
        std::vector<std::string> words;
        size_t l;
        size_t r;
        size_t width;
        std::string exp;
    };

    const TestCase test_cases[] = {
        { { "a" }, 0, 1, 5, "a    " },
        { { "a", "b" }, 0, 2, 5, "a b  " },
        { { "a", "b" }, 1, 2, 5, "b    " },
        { { "a", "b", "c" }, 0, 3, 5, "a b c" },
        { { "a", "b", "c" }, 1, 3, 5, "b c  " },
    };

    for (const auto& tc : test_cases) {
        const auto act = leftJustify(tc.words, tc.l, tc.r, tc.width);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", l: " << tc.l
                      << ", r: " << tc.r
                      << ", width: " << tc.width
                      << "), exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}

void test_leftRightJustify()
{
    struct TestCase {
        std::vector<std::string> words;
        size_t l;
        size_t r;
        size_t width;
        std::string exp;
    };

    const TestCase test_cases[] = {
        { { "a" }, 0, 1, 5, "a    " },
        { { "a", "b" }, 0, 2, 5, "a   b" },
        { { "a", "b" }, 1, 2, 5, "b    " },
        { { "a", "b", "c" }, 0, 3, 5, "a b c" },
        { { "a", "b", "c" }, 0, 3, 6, "a  b c" },
        { { "a", "b", "c" }, 0, 3, 7, "a  b  c" },
        { { "This", "is", "an" }, 0, 3, 16, "This    is    an" },
    };

    for (const auto& tc : test_cases) {
        const auto act = leftRightJustify(tc.words, tc.l, tc.r, tc.width);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", l: " << tc.l
                      << ", r: " << tc.r
                      << ", width: " << tc.width
                      << "), exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}

void test_fullJustify()
{
    struct TestCase {
        std::vector<std::string> words;
        int maxWidth;
        std::vector<std::string> exp;
    };

    const TestCase test_cases[] = {
        { { "Imma", "be" }, 7, { "Imma be" } },
        { { "Imma", "be" }, 8, { "Imma be " } },
        { { "Imma", "be", "real" }, 7, { "Imma be", "real   " } },
        { { "Imma", "be", "real" }, 6, { "Imma  ", "be    ", "real  " } },
        { { "Imma", "be", "real" }, 8, { "Imma  be", "real    " } },
        { { "This", "is", "an", "example", "of", "text", "justification." }, 16, { "This    is    an", "example  of text", "justification.  " } },
        { { "What", "must", "be", "acknowledgment", "shall", "be" }, 16, { "What   must   be", "acknowledgment  ", "shall be        " } },
        { { "Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do" }, 20, { "Science  is  what we", "understand      well", "enough to explain to", "a  computer.  Art is", "everything  else  we", "do                  " } },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.fullJustify(tc.words, tc.maxWidth);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", width: " << tc.maxWidth
                      << "), exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
}

int main()
{
    test_leftJustify();
    test_leftRightJustify();
    test_fullJustify();
    return 0;
}
