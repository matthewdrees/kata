// LeetCode 30. Substring with Concatenation of All Words.
#include <algorithm>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "leetcode.hpp"

using WordsMap = std::unordered_map<std::string, int16_t>;

void inc_word_in_map(WordsMap& words_map, const std::string& word)
{
    if (!words_map.insert({ word, 1 }).second) {
        ++words_map[word];
    }
}
void dec_word_in_map(WordsMap& words_map, const std::string& word)
{
    auto it = words_map.find(word);
    if (it->second == 1) {
        words_map.erase(it);
    } else {
        --it->second;
    }
}

WordsMap get_words_map(const std::vector<std::string>& words)
{
    std::unordered_map<std::string, int16_t> words_map;
    for (const auto& w : words) {
        inc_word_in_map(words_map, w);
    }
    return words_map;
}

class StringCircularQueue {
    std::vector<std::string> queue;
    size_t idx { 0 };
    size_t cur_size { 0 };

public:
    explicit StringCircularQueue(size_t size_)
        : queue(size_)
    {
    }

    bool full() const { return cur_size == queue.size(); }
    const std::string& front() const { return queue[idx]; }
    void push_back(const std::string& s)
    {
        queue[idx++] = s;
        if (idx >= queue.size()) {
            idx = 0;
        }
        if (cur_size < queue.size()) {
            ++cur_size;
        }
    }
    size_t empty() const { return cur_size == 0; }
    void clear()
    {
        idx = 0;
        cur_size = 0;
    }
};

void findSubstringOnOffset(size_t offset, const std::string& s, const WordsMap& words_map, size_t word_size,
    size_t words_size, std::vector<int>& substring_indexes)
{
    WordsMap cur_words_map;
    StringCircularQueue word_queue(words_size);

    const size_t i_end = s.size() + 1 - word_size;
    for (size_t i = offset; i < i_end; i += word_size) {
        const std::string w(&s[i], word_size);
        if (words_map.find(w) != words_map.end()) {
            if (word_queue.full()) {
                dec_word_in_map(cur_words_map, word_queue.front());
            }
            word_queue.push_back(w);
            inc_word_in_map(cur_words_map, w);
            if (words_map == cur_words_map) {
                substring_indexes.push_back(i - word_size * (words_size - 1));
            }
        } else if (!word_queue.empty()) {
            word_queue.clear();
            cur_words_map.clear();
        }
    }
}

class Solution {

public:
    std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words)
    {
        const auto words_map = get_words_map(words);
        const size_t word_size = words.at(0).size();
        std::vector<int> substring_indexes;
        for (size_t offset = 0; offset < word_size; ++offset) {
            findSubstringOnOffset(offset, s, words_map, word_size, words.size(), substring_indexes);
        }
        return substring_indexes;
    }
};

int main()
{
    struct TestCase {
        std::string s;
        std::vector<std::string> words;
        std::vector<int> exp;
    };
    const TestCase test_cases[] = {
        { "abcdef", { "ab", "cd", "ef" }, { 0 } },
        { "barfoothefoobarman", { "foo", "bar" }, { 0, 9 } },
        { "wordgoodgoodgoodbestword", { "word", "good", "best", "word" }, {} },
        { "barfoofoobarthefoobarman", { "bar", "foo", "the" }, { 6, 9, 12 } },
        { "ababababa", { "aba", "bab" }, { 0, 1, 2, 3 } },
    };
    Solution solution;
    for (const auto& tc : test_cases) {
        auto act = solution.findSubstring(tc.s, tc.words);
        std::sort(act.begin(), act.end());
        if (tc.exp != act) {
            std::cerr << "Fail. s: " << tc.s
                      << ", words: " << leetcode::to_string(tc.words)
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
    return 0;
}