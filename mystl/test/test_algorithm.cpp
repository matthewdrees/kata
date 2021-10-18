#include "mystl/algorithm.hpp"

#include <iostream>
#include <sstream>
#include <vector>

template <class T>
std::string vec_to_string(const std::vector<T> &v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto &i : v)
    {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

int test_all_of()
{
    struct TestCase
    {
        std::vector<int> v;
        bool expected;
    };
    const TestCase test_cases[] = {
        {{}, true},
        {{1}, true},
        {{2}, false},
        {{1, 2}, false},
        {{2, 1}, false},
        {{1, 1}, true},
        {{1, 2, 3}, false},
        {{1, 1, 1}, true},
        {{1, 1, 1, 2}, false},
        {{2, 1, 1, 1}, false},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        const auto actual = all_of(tc.v.begin(), tc.v.end(), [](int i)
                                   { return i == 1; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_any_of()
{
    struct TestCase
    {
        std::vector<int> v;
        bool expected;
    };
    const TestCase test_cases[] = {
        {{}, false},
        {{1}, true},
        {{2}, false},
        {{1, 2}, true},
        {{2, 1}, true},
        {{1, 1}, true},
        {{2, 2}, false},
        {{1, 2, 3}, true},
        {{1, 1, 1}, true},
        {{2, 3, 0}, false},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        const auto actual = any_of(tc.v.begin(), tc.v.end(), [](int i)
                                   { return i == 1; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_none_of()
{
    struct TestCase
    {
        std::vector<int> v;
        bool expected;
    };
    const TestCase test_cases[] = {
        {{}, true},
        {{1}, false},
        {{2}, true},
        {{1, 2}, false},
        {{2, 1}, false},
        {{1, 1}, false},
        {{2, 2}, true},
        {{1, 2, 3}, false},
        {{1, 1, 1}, false},
        {{2, 3, 0}, true},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        const auto actual = none_of(tc.v.begin(), tc.v.end(), [](int i)
                                    { return i == 1; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_for_each()
{
    struct TestCase
    {
        std::vector<int> v;
        int expected;
    };
    struct Sum
    {
        void operator()(int i) { sum += i; }
        int sum{0};
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{0}, 0},
        {{1}, 1},
        {{2}, 2},
        {{1, 2}, 3},
        {{1, 2, 3}, 6},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        Sum s;
        const auto actual = for_each(tc.v.begin(), tc.v.end(), s);
        if (tc.expected != actual.sum)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual.sum
                      << "\n";
        }
    }
    return num_fails;
}

int test_for_each_n()
{
    struct TestCase
    {
        std::vector<int> v;
        int n;
        std::vector<int> expected;
    };
    const TestCase test_cases[] = {
        {{}, 0, {}},
        {{0}, 1, {1}},
        {{1}, 1, {2}},
        {{1}, 0, {1}},
        {{2}, 1, {3}},
        {{1, 2}, 0, {1, 2}},
        {{1, 2}, 1, {2, 2}},
        {{1, 2}, 2, {2, 3}},
        {{1, 2, 3}, 0, {1, 2, 3}},
        {{1, 2, 3}, 1, {2, 2, 3}},
        {{1, 2, 3}, 2, {2, 3, 3}},
        {{1, 2, 3}, 3, {2, 3, 4}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto v = tc.v;
        for_each_n(v.begin(), tc.n, [](int &i)
                   { i += 1; });
        if (tc.expected != v)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ", n: " << tc.n << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(v)
                      << "\n";
        }
    }
    return num_fails;
}

int test_count()
{
    struct TestCase
    {
        std::vector<int> v;
        int n;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0, 0},
        {{0}, 1, 0},
        {{1}, 1, 1},
        {{1, 2}, 0, 0},
        {{1, 2}, 1, 1},
        {{1, 2}, 2, 1},
        {{1, 1}, 2, 0},
        {{1, 1}, 1, 2},
        {{1, 2, 3}, 0, 0},
        {{1, 2, 3}, 1, 1},
        {{1, 2, 3}, 2, 1},
        {{1, 2, 3}, 3, 1},
        {{1, 2, 3}, 4, 0},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto actual = count(tc.v.begin(), tc.v.end(), tc.n);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ", n: " << tc.n << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_count_if()
{
    struct TestCase
    {
        std::vector<int> v;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{0}, 1},
        {{1}, 0},
        {{0, 0}, 2},
        {{1, 0}, 1},
        {{0, 1}, 1},
        {{1, 1}, 0},
        {{1, 1, 3}, 0},
        {{1, 2, 3}, 1},
        {{2, 4, 3}, 2},
        {{2, 4, 6}, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto actual = count_if(tc.v.begin(), tc.v.end(), [](int i)
                               { return i % 2 == 0; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_mismatch()
{
    struct TestCase
    {
        std::vector<int> v1;
        std::vector<int> v2;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, {}, 0},
        {{0}, {0}, 1},
        {{0}, {1}, 0},
        {{1}, {0}, 0},
        {{1, 2}, {1, 2}, 2},
        {{1, 3}, {1, 2}, 1},
        {{1, 2, 3}, {1, 2, 3}, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto p = ::mismatch(tc.v1.begin(), tc.v1.end(), tc.v2.begin());
        const auto actual1 = std::distance(tc.v1.begin(), p.first);
        const auto actual2 = std::distance(tc.v2.begin(), p.second);

        if (tc.expected != actual1 || tc.expected != actual2)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v1: " << vec_to_string(tc.v1)
                      << ", v2: " << vec_to_string(tc.v2) << ")"
                      << ", expected: " << tc.expected
                      << ", actual1: " << actual1
                      << ", actual2: " << actual2
                      << "\n";
        }
    }
    return num_fails;
}

int test_find()
{
    struct TestCase
    {
        std::vector<int> v;
        int value;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 5, 0},
        {{0}, 0, 0},
        {{0}, 1, 1},
        {{0, 1}, 1, 1},
        {{0, 1}, 0, 0},
        {{0, 1}, 3, 2},
        {{0, 1, 2}, -1, 3},
        {{0, 1, 2}, 0, 0},
        {{0, 1, 2}, 1, 1},
        {{0, 1, 2}, 2, 2},
        {{0, 1, 2}, 5, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = find(tc.v.begin(), tc.v.end(), tc.value);
        const auto actual = std::distance(tc.v.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v)
                      << ", value: " << tc.value << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_find_if()
{
    struct TestCase
    {
        std::vector<int> v;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{2}, 0},
        {{1}, 1},
        {{0, 1}, 0},
        {{1, 2}, 1},
        {{1, 3}, 2},
        {{4, 3, 1}, 0},
        {{5, 6, 1}, 1},
        {{5, 3, 2}, 2},
        {{5, 3, 1}, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = find_if(tc.v.begin(), tc.v.end(), [](const auto &i)
                          { return i % 2 == 0; });
        const auto actual = std::distance(tc.v.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_find_if_not()
{
    struct TestCase
    {
        std::vector<int> v;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{2}, 0},
        {{1}, 1},
        {{0, 1}, 0},
        {{1, 2}, 1},
        {{1, 3}, 2},
        {{4, 3, 1}, 0},
        {{5, 6, 1}, 1},
        {{5, 3, 2}, 2},
        {{5, 3, 1}, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = find_if_not(tc.v.begin(), tc.v.end(), [](const auto &i)
                              { return i % 2 == 1; });
        const auto actual = std::distance(tc.v.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_find_end()
{
    struct TestCase
    {
        std::vector<int> v1;
        std::vector<int> v2;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, {}, 0},
        {{1}, {1}, 0},
        {{0}, {1}, 1},
        {{1}, {0}, 1},
        {{1, 2}, {1}, 0},
        {{1, 1}, {1}, 1},
        {{1, 2}, {2}, 1},
        {{1, 2}, {3}, 2},
        {{1, 2}, {1, 2}, 0},
        {{1, 2, 3}, {1, 2}, 0},
        {{1, 2, 3}, {2, 3}, 1},
        {{1, 2, 3}, {1, 2, 3}, 0},
        {{1, 2, 3, 4}, {1}, 0},
        {{1, 2, 3, 4}, {2}, 1},
        {{1, 2, 3, 4}, {3}, 2},
        {{1, 2, 3, 4}, {4}, 3},
        {{1, 2, 3, 4}, {5}, 4},
        {{1, 2, 3, 4}, {1, 2}, 0},
        {{1, 2, 3, 4}, {2, 3}, 1},
        {{3, 4, 3, 4}, {3, 4}, 2},
        {{1, 2, 3, 4}, {4, 5}, 4},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = find_end(tc.v1.begin(), tc.v1.end(), tc.v2.begin(), tc.v2.end());
        const auto actual = std::distance(tc.v1.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v1: " << vec_to_string(tc.v1)
                      << ", v2: " << vec_to_string(tc.v2) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_find_first_of()
{
    struct TestCase
    {
        std::vector<int> v1;
        std::vector<int> v2;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, {}, 0},
        {{1}, {}, 1},
        {{}, {1}, 0},
        {{0}, {1}, 1},
        {{1}, {0}, 1},
        {{1}, {1}, 0},
        {{1, 1}, {0}, 2},
        {{1, 1}, {1}, 0},
        {{1, 2}, {1}, 0},
        {{1, 2}, {2}, 1},
        {{1, 2}, {0, 0}, 2},
        {{1, 2}, {0, 1}, 0},
        {{1, 2}, {0, 2}, 1},
        {{1, 2}, {0, 3}, 2},
        {{1, 2}, {1, 0}, 0},
        {{1, 2}, {2, 0}, 1},
        {{1, 2}, {3, 0}, 2},
        {{1, 2, 3}, {0, 0}, 3},
        {{1, 2, 3}, {0, 1}, 0},
        {{1, 2, 3}, {0, 2}, 1},
        {{1, 2, 3}, {0, 3}, 2},
        {{1, 2, 3}, {1, 0}, 0},
        {{1, 2, 3}, {2, 0}, 1},
        {{1, 2, 3}, {3, 0}, 2},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = find_first_of(tc.v1.begin(), tc.v1.end(), tc.v2.begin(), tc.v2.end());
        const auto actual = std::distance(tc.v1.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v1: " << vec_to_string(tc.v1)
                      << ", v2: " << vec_to_string(tc.v2) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_adjacent_find()
{
    struct TestCase
    {
        std::vector<int> v;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, 0},
        {{1}, 1},
        {{0, 1}, 2},
        {{1, 1}, 0},
        {{1, 2, 3}, 3},
        {{1, 1, 3}, 0},
        {{1, 2, 2}, 1},
        {{1, 2, 3, 4}, 4},
        {{1, 1, 3, 4}, 0},
        {{1, 2, 2, 4}, 1},
        {{1, 2, 3, 3}, 2},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = adjacent_find(tc.v.begin(), tc.v.end());
        const auto actual = std::distance(tc.v.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_search()
{
    struct TestCase
    {
        std::vector<int> v1;
        std::vector<int> v2;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, {}, 0},
        {{1}, {1}, 0},
        {{0}, {1}, 1},
        {{1, 2}, {1}, 0},
        {{1, 1}, {1}, 0},
        {{1, 2}, {2}, 1},
        {{1, 2}, {3}, 2},
        {{1, 2}, {1, 2}, 0},
        {{1, 2, 3}, {1, 2}, 0},
        {{1, 2, 3}, {2, 3}, 1},
        {{1, 2, 3}, {1, 2, 3}, 0},
        {{1, 2, 3, 4}, {1}, 0},
        {{1, 2, 3, 4}, {2}, 1},
        {{1, 2, 3, 4}, {3}, 2},
        {{1, 2, 3, 4}, {4}, 3},
        {{1, 2, 3, 4}, {5}, 4},
        {{1, 2, 3, 4}, {1, 2}, 0},
        {{1, 2, 3, 4}, {2, 3}, 1},
        {{3, 4, 3, 4}, {3, 4}, 0},
        {{1, 2, 3, 4}, {4, 5}, 4},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = ::search(tc.v1.begin(), tc.v1.end(), tc.v2.begin(), tc.v2.end());
        const auto actual = std::distance(tc.v1.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v1: " << vec_to_string(tc.v1)
                      << ", v2: " << vec_to_string(tc.v2) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_search_n()
{
    struct TestCase
    {
        std::vector<int> v;
        int n;
        int value;
        std::ptrdiff_t expected;
    };
    const TestCase test_cases[] = {
        {{}, -1, 1, 0},
        {{}, 0, 1, 0},
        {{}, 1, 1, 0},
        {{1}, -1, 1, 0},
        {{1}, 0, 1, 0},
        {{1}, 1, 1, 0},
        {{1}, 1, 2, 1},
        {{1, 1}, 1, 1, 0},
        {{1, 1}, 2, 1, 0},
        {{1, 1}, 3, 1, 2},
        {{1, 2}, 1, 1, 0},
        {{1, 2}, 1, 2, 1},
        {{1, 2, 2}, 1, 2, 1},
        {{1, 2, 2}, 2, 2, 1},
        {{2, 2, 2}, 3, 2, 0},
        {{2, 2, 2}, 2, 2, 0},
        {{2, 2, 2}, 3, 2, 0},
        {{2, 2, 2}, 4, 2, 3},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        auto it = search_n(tc.v.begin(), tc.v.end(), tc.n, tc.value);
        const auto actual = std::distance(tc.v.begin(), it);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ", n: " << tc.n << ", value: " << tc.value << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return num_fails;
}

int test_copy()
{
    struct TestCase
    {
        std::vector<int> v;
        std::ptrdiff_t first_index;
        std::ptrdiff_t last_index;
        std::vector<int> expected;
    };
    const TestCase test_cases[] = {
        {{}, 0, 0, {}},
        {{1}, 0, 1, {1}},
        {{1, 2}, 0, 2, {1, 2}},
        {{1, 2}, 0, 1, {1, 0}},
        {{1, 2}, 1, 2, {2, 0}},
        {{1, 2, 3}, 0, 1, {1, 0, 0}},
        {{1, 2, 3}, 0, 2, {1, 2, 0}},
        {{1, 2, 3}, 0, 3, {1, 2, 3}},
        {{1, 2, 3}, 1, 1, {0, 0, 0}},
        {{1, 2, 3}, 1, 2, {2, 0, 0}},
        {{1, 2, 3}, 1, 3, {2, 3, 0}},
        {{1, 2, 3}, 2, 2, {0, 0, 0}},
        {{1, 2, 3}, 2, 3, {3, 0, 0}},
        {{1, 2, 3}, 3, 3, {0, 0, 0}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        std::vector<int> actual(tc.expected.size(), 0);
        auto it = ::copy(tc.v.begin() + tc.first_index, tc.v.begin() + tc.last_index, actual.begin());
        const auto actual_it_distance = std::distance(actual.begin(), it);
        const ptrdiff_t expected_it_distance = tc.last_index - tc.first_index;
        if (tc.expected != actual || expected_it_distance != actual_it_distance)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v)
                      << ", first_index: " << tc.first_index << ", last_index: " << tc.last_index << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(actual)
                      << ", expected it distance: " << expected_it_distance
                      << ", actual it distance: " << actual_it_distance
                      << "\n";
        }
    }
    return num_fails;
}

int test_copy_if()
{
    struct TestCase
    {
        std::vector<int> v;
        std::vector<int> expected;
    };
    const TestCase test_cases[] = {
        {{}, {}},
        {{1}, {}},
        {{2}, {2}},
        {{1, 2}, {2}},
        {{2, 1}, {2}},
        {{1, 2, 3}, {2}},
        {{1, 2, 3, 4}, {2, 4}},
        {{2, 3, 4, 5}, {2, 4}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        std::vector<int> actual;
        (void)::copy_if(tc.v.begin(), tc.v.end(), std::back_inserter(actual), [=](const int i)
                        { return i % 2 == 0; });
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(actual)
                      << "\n";
        }
    }
    return num_fails;
}

int test_copy_backward()
{
    struct TestCase
    {
        std::vector<int> v;
        std::vector<int> expected;
    };
    const TestCase test_cases[] = {
        {{}, {}},
        {{1}, {1}},
        {{1, 2}, {1, 2}},
        {{1, 2, 3}, {1, 2, 3}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        std::vector<int> actual(tc.v.size(), 0);
        const auto it = ::copy_backward(tc.v.begin(), tc.v.end(), actual.end());
        const auto ret_it_dist = std::distance(actual.begin(), it);
        if (tc.expected != actual || ret_it_dist != 0)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.v) << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(actual)
                      << ", return it distace: " << ret_it_dist
                      << "\n";
        }
    }
    return num_fails;
}

namespace // unnamed
{
    // CantCopy class for testing stuff that can only move.
    class CantCopy
    {
        int i;

    public:
        CantCopy() : i(0) {}
        CantCopy(int i_) : i(i_) {}
        CantCopy(const CantCopy &) = delete;
        CantCopy &operator=(const CantCopy &) = delete;
        CantCopy(CantCopy &&o) noexcept = default;
        CantCopy &operator=(CantCopy &&o) noexcept = default;
        int getI() const noexcept { return i; }
    };
    bool operator==(const CantCopy &lhs, const CantCopy &rhs)
    {
        return lhs.getI() == rhs.getI();
    }
    std::ostream &operator<<(std::ostream &os, const CantCopy &cc)
    {
        os << cc.getI();
        return os;
    }
} // Unnamed namespace

int test_move()
{
    struct TestCase
    {
        std::vector<int> v;
        std::vector<int> expected;
    };

    const TestCase test_cases[] = {
        {{}, {}},
        {{1}, {1}},
        {{1, 2}, {1, 2}},
        {{1, 2, 3}, {1, 2, 3}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        std::vector<CantCopy> v2(tc.v.size());
        // Move constructor
        (void)::move(tc.v.begin(), tc.v.end(), v2.begin());
        // Move assignment
        std::vector<CantCopy> actual(tc.v.size());
        const auto it = ::move(v2.begin(), v2.end(), actual.begin());
        const ptrdiff_t it_distance = std::distance(it, actual.end());
        if (!std::equal(tc.expected.begin(), tc.expected.end(), actual.begin(), actual.end(), [](const auto &i1, const auto &i2)
                        { return i1 == i2; }) ||
            it_distance != 0)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.expected) << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(actual)
                      << ", it distance != 0: " << it_distance
                      << "\n";
        }
    }
    return num_fails;
}

int test_move_backward()
{
    struct TestCase
    {
        std::vector<int> v;
        std::vector<int> expected;
    };
    const TestCase test_cases[] = {
        {{}, {}},
        {{1}, {1}},
        {{1, 2}, {1, 2}},
        {{1, 2, 3}, {1, 2, 3}},
    };
    int num_fails = 0;
    for (const auto &tc : test_cases)
    {
        std::vector<CantCopy> v2(tc.v.size());
        // Move constructor
        (void)::move_backward(tc.v.begin(), tc.v.end(), v2.end());
        // Move assignment
        std::vector<CantCopy> actual(tc.v.size());
        const auto it = ::move_backward(v2.begin(), v2.end(), actual.end());
        const ptrdiff_t it_distance = std::distance(actual.begin(), it);
        if (!std::equal(tc.expected.begin(), tc.expected.end(), actual.begin(), actual.end(), [](const auto &i1, const auto &i2)
                        { return i1 == i2; }) ||
            it_distance != 0)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(tc.expected) << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(actual)
                      << ", it distance != 0: " << it_distance
                      << "\n";
        }
    }
    return num_fails;
}

int test_fill()
{
    std::vector<int> v = {0, 0, 0};
    ::fill(v.begin(), v.begin() + 2, 1);
    const std::vector<int> expected = {1, 1, 0};
    int num_fails = 0;
    if (expected != v)
    {
        ++num_fails;
        std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(v) << ")"
                  << ", expected: " << vec_to_string(expected)
                  << ", actual: " << vec_to_string(v)
                  << "\n";
    }
    return num_fails;
}

int test_fill_n()
{
    std::vector<int> v = {0, 0, 0};
    ::fill_n(v.begin(), 2, 1);
    const std::vector<int> expected = {1, 1, 0};
    int num_fails = 0;
    if (expected != v)
    {
        ++num_fails;
        std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(v) << ")"
                  << ", expected: " << vec_to_string(expected)
                  << ", actual: " << vec_to_string(v)
                  << "\n";
    }
    return num_fails;
}

int test_transform()
{
    const std::vector<int> v = {1, 2, 3};
    std::vector<int> v2 = {0, 0, 0};
    ::transform(v.begin(), v.end(), v2.begin(), [](const auto i)
                { return i + 1; });
    const std::vector<int> expected = {2, 3, 4};
    int num_fails = 0;
    if (expected != v2)
    {
        ++num_fails;
        std::cerr << "FAIL, " << __FUNCTION__ << "(v: " << vec_to_string(v) << ")"
                  << ", expected: " << vec_to_string(expected)
                  << ", actual: " << vec_to_string(v2)
                  << "\n";
    }
    return num_fails;
}

int main()
{
    const int num_fails = test_all_of() +
                          test_any_of() +
                          test_none_of() +
                          test_for_each() +
                          test_for_each_n() +
                          test_count() +
                          test_count_if() +
                          test_mismatch() +
                          test_find() +
                          test_find_if() +
                          test_find_if_not() +
                          test_find_end() +
                          test_find_first_of() +
                          test_adjacent_find() +
                          test_search() +
                          test_search_n() +
                          test_copy() +
                          test_copy_if() +
                          test_copy_backward() +
                          test_move() +
                          test_move_backward() +
                          test_fill() +
                          test_fill_n() +
                          test_transform();

    return num_fails == 0 ? 0 : 1;
}
