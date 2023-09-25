// LeetCode p68. Text Justification.

#include "leetcode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

std::string leftJustify(const std::vector<std::string>& words, size_t startIndex, size_t endIndex, int maxWidth)
{
    std::string line(static_cast<size_t>(maxWidth), ' ');
    auto it = line.begin();
    for (size_t i = startIndex; i < endIndex; ++i) {
        it = std::copy(words[i].begin(), words[i].end(), it);
        ++it;
    }
    return line;
}

std::string leftRightJustify(const std::vector<std::string>& words, size_t startIndex, size_t endIndex, int maxWidth)
{
    assert(maxWidth >= 0);
    assert(endIndex >= startIndex);
    const size_t numWords = endIndex - startIndex;
    if (endIndex - startIndex < 2) {
        return leftJustify(words, startIndex, endIndex, maxWidth);
    }
    const size_t totalSpaces = static_cast<size_t>(maxWidth) - std::accumulate(words.begin() + startIndex, words.begin() + endIndex, 0u, [](size_t s, const std::string& w) { return s + w.size(); });
    const size_t minSpacesBetweenWords = totalSpaces / (numWords - 1);
    size_t remainderSpacesBetweenWords = totalSpaces % (numWords - 1);

    std::string line(static_cast<size_t>(maxWidth), ' ');
    auto it = line.begin();
    for (size_t i = startIndex; i < endIndex; ++i) {
        it = std::copy(words[i].begin(), words[i].end(), it);
        it += minSpacesBetweenWords;
        if (remainderSpacesBetweenWords > 0) {
            ++it;
            remainderSpacesBetweenWords -= 1;
        }
    }
    return line;
}

class Solution {
public:
    std::vector<std::string> fullJustify(const std::vector<std::string>& words, int maxWidth)
    {
        std::vector<std::string> output;
        size_t startIndex = 0;
        while (startIndex < words.size()) {
            size_t lineLength = 0;
            size_t endIndex = startIndex;
            for (; endIndex < words.size(); ++endIndex) {
                lineLength += 1 + words[endIndex].size();
                if (lineLength > static_cast<size_t>(maxWidth + 1)) {
                    output.push_back(leftRightJustify(words, startIndex, endIndex, maxWidth));
                    break;
                }
            }
            if (endIndex == words.size()) {
                output.push_back(leftJustify(words, startIndex, endIndex, maxWidth));
                break;
            }
            startIndex = endIndex;
        }
        return output;
    }
};

void test_leftJustify()
{
    struct TestCase {
        std::vector<std::string> words;
        size_t startIndex;
        size_t endIndex;
        int maxWidth;
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
        const auto act = leftJustify(tc.words, tc.startIndex, tc.endIndex, tc.maxWidth);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", startIndex: " << tc.startIndex
                      << ", endIndex: " << tc.endIndex
                      << ", width: " << tc.maxWidth
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
        size_t startIndex;
        size_t endIndex;
        int maxWidth;
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
        const auto act = leftRightJustify(tc.words, tc.startIndex, tc.endIndex, tc.maxWidth);
        if (tc.exp != act) {
            std::cerr << "fail. leftJustify(words: "
                      << leetcode::to_string(tc.words)
                      << ", startIndex: " << tc.startIndex
                      << ", endIndex: " << tc.endIndex
                      << ", width: " << tc.maxWidth
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
        { { "Imma", "be", "real" }, 8, { "Imma be ", "real    " } },
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
