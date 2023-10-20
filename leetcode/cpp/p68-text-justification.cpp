// LeetCode p68. Text Justification.

#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <span>
#include <vector>

std::string leftJustify(std::span<std::string const> words, size_t width)
{
    std::string line(width, ' ');
    auto it = line.begin();
    for (const auto& word : words) {
        it = std::copy(word.begin(), word.end(), it);
        ++it;
    }
    return line;
}

std::string leftRightJustify(std::span<std::string const> words, size_t width, size_t lineLen)
{
    if (words.size() < 2) {
        return leftJustify(words, width);
    }
    const size_t totalSpaces = width + words.size() - lineLen;
    const size_t minSpacesBetweenWords = totalSpaces / (words.size() - 1);
    size_t remainderSpacesBetweenWords = totalSpaces % (words.size() - 1);

    std::string line(width, ' ');
    auto it = line.begin();
    for (const auto& word : words) {
        it = std::copy(word.begin(), word.end(), it);
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
        auto l = words.begin();
        size_t lineLen = 0;
        for (auto r = l; r != words.end(); ++r) {
            const auto& word = *r;
            if (lineLen + word.size() > width) {
                output.push_back(leftRightJustify(std::span(l, r), width, lineLen));
                l = r;
                lineLen = 0;
            }
            lineLen += word.size() + 1;
        }
        if (l != words.end()) {
            output.push_back(leftJustify(std::span(l, words.end()), width));
        }
        return output;
    }
};

void test_leftJustify()
{
    struct TestCase {
        std::vector<std::string> words;
        size_t width;
        std::string exp;
    };

    const TestCase test_cases[] = {
        { { "a" }, 1, "a" },
        { { "a" }, 5, "a    " },
        { { "a", "b" }, 3, "a b" },
        { { "a", "b" }, 4, "a b " },
        { { "a", "b", "c" }, 5, "a b c" },
        { { "a", "b", "c" }, 6, "a b c " },
    };

    for (const auto& tc : test_cases) {
        const auto act = leftJustify(std::span(tc.words), tc.width);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", width: " << tc.width
                      << "), exp: '" << tc.exp
                      << "', act: '" << act
                      << "'\n";
        }
    }
}

void test_leftRightJustify()
{
    struct TestCase {
        std::vector<std::string> words;
        size_t width;
        size_t lineLen;
        std::string exp;
    };

    const TestCase test_cases[] = {
        { { "a" }, 1, 2, "a" },
        { { "a" }, 2, 2, "a " },
        { { "a" }, 5, 2, "a    " },
        { { "a", "b" }, 3, 4, "a b" },
        { { "a", "b" }, 4, 4, "a  b" },
        { { "a", "b" }, 5, 4, "a   b" },
        { { "a", "b", "c" }, 5, 6, "a b c" },
        { { "a", "b", "c" }, 6, 6, "a  b c" },
        { { "a", "b", "c" }, 7, 6, "a  b  c" },
        { { "a", "b", "c" }, 8, 6, "a   b  c" },
        { { "This", "is", "an" }, 16, 11, "This    is    an" },
    };

    for (const auto& tc : test_cases) {
        const auto act = leftRightJustify(std::span(tc.words), tc.width, tc.lineLen);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", width: " << tc.width
                      << ", lineLen: " << tc.lineLen
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
