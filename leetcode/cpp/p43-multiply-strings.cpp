// LeetCode 43. Multiply Strings.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "leetcode.hpp"

void multiply1(const std::string& num, int x, size_t stage_num, std::vector<int8_t>& v)
{
    stage_num = v.size() - stage_num - 1;
    int carry = 0;
    for (auto it = num.rbegin(); it != num.rend(); ++it) {
        const int val = (*it - 48) * x + v[stage_num] + carry;
        const auto divmod = std::div(val, 10);
        carry = divmod.quot;
        v[stage_num--] = divmod.rem;
    }
    while (carry != 0) {
        const int val = carry + v[stage_num];
        const auto divmod = std::div(val, 10);
        carry = divmod.quot;
        v[stage_num--] = divmod.rem;
    }
}

std::string get_numstring_from_array(std::vector<int8_t>& v)
{
    auto it = std::find_if(v.begin(), v.end(), [](const auto val) { return val != 0; });
    if (it != v.end()) {
        std::transform(it, v.end(), it, [](const auto val) { return val + 48; });
        return std::string(it, v.end());
    }
    return "0";
}

class Solution {
public:
    std::string multiply(const std::string& num1, const std::string& num2)
    {
        std::vector<int8_t> v(num1.size() + num2.size());
        size_t stage_num = 0;
        for (auto it = num2.rbegin(); it != num2.rend(); ++it) {
            multiply1(num1, *it - 48, stage_num, v);
            stage_num += 1;
        }

        return get_numstring_from_array(v);
    }
};

void test_get_numstring_from_array()
{
    struct TestCase {
        std::vector<int8_t> v;
        std::string exp;
    };
    TestCase test_cases[] = {
        { { 0 }, "0" },
        { { 1 }, "1" },
        { { 0, 1 }, "1" },
        { { 7, 8, 9 }, "789" },
        { { 7, 0, 9 }, "709" },
        { { 0, 0, 7, 0, 9 }, "709" },
        { { 0, 0, 7, 0, 9, 0 }, "7090" },
    };
    for (const auto& tc : test_cases) {
        auto v = tc.v;
        const auto act = get_numstring_from_array(v);
        if (tc.exp != act) {
            std::cerr << __FUNCTION__ << ", FAIL, "
                      << "v: " << leetcode::to_string(tc.v)
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}

void test_multiply1()
{
    struct TestCase {
        std::vector<int8_t> v;
        std::string num;
        int x;
        size_t stage_num;
        std::vector<int8_t> exp;
    };

    TestCase test_cases[] = {
        { { 0, 0 }, "0", 3, 0, { 0, 0 } },
        { { 0, 0 }, "1", 3, 0, { 0, 3 } },
        { { 0, 0 }, "1", 3, 1, { 3, 0 } },
        { { 0, 1 }, "0", 3, 0, { 0, 1 } },
        { { 0, 1 }, "1", 0, 0, { 0, 1 } },
        { { 0, 1 }, "1", 3, 0, { 0, 4 } },
        { { 0, 1 }, "11", 3, 0, { 3, 4 } },
        { { 0, 0, 1 }, "51", 3, 0, { 1, 5, 4 } },
        { { 0, 0, 0, 0, 0, 0 }, "123", 6, 0, { 0, 0, 0, 7, 3, 8 } },
        { { 0, 0, 0, 7, 3, 8 }, "123", 5, 1, { 0, 0, 6, 8, 8, 8 } },
        { { 0, 0, 6, 8, 8, 8 }, "123", 4, 2, { 0, 5, 6, 0, 8, 8 } },
    };
    for (const auto& tc : test_cases) {
        auto act = tc.v;
        multiply1(tc.num, tc.x, tc.stage_num, act);
        if (tc.exp != act) {
            std::cerr << __FUNCTION__ << ", FAIL, "
                      << "v: " << leetcode::to_string(tc.v)
                      << "x: " << tc.x
                      << "stage_num: " << tc.stage_num
                      << ", exp: " << leetcode::to_string(tc.exp)
                      << ", act: " << leetcode::to_string(act)
                      << "\n";
        }
    }
}

void test_multiply()
{
    struct TestCase {
        std::string num1;
        std::string num2;
        std::string exp;
    };
    TestCase test_cases[] = {
        { "2", "3", "6" },
        { "123", "456", "56088" },
        { "456", "123", "56088" },
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.multiply(tc.num1, tc.num2);
        if (tc.exp != act) {
            std::cerr << __FUNCTION__ << ", FAIL, "
                      << "num1: " << tc.num1
                      << "num2: " << tc.num2
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}

int main()
{
    test_get_numstring_from_array();
    test_multiply1();
    test_multiply();
    return 0;
}