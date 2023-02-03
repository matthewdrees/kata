// perf-ninja vectorization_2 solution.
#include <array>
#include <cstdint>

#include <iostream>

// Assume this constant never changes
constexpr std::size_t N = 64 * 1024;

using Blob = std::array<uint16_t, N>;

uint16_t checksum(const Blob &blob)
{
    uint16_t acc = 0;
    for (auto value : blob)
    {
        acc += value;
        acc += acc < value; // add carry
    }
    return acc;
}

int main()
{
    struct TestCase
    {
        Blob b;
        uint16_t exp;
    };

    TestCase test_cases[] = {
        {{}, 0},
        {{1}, 1},
        {{2}, 2},
        {{3}, 3},
        {{255}, 255},
        {{255, 255, 255, 255, 255}, 1275},
    };

    for (const auto &tc : test_cases)
    {
        const auto act = checksum(tc.b);
        if (tc.exp != act)
        {
            std::cerr << "fail, exp: " << tc.exp
                      << ", act: " << act << "\n";
        }
    }

    {
        Blob b;
        b.fill(255);
        const auto act = checksum(b);
        const uint16_t exp = 255;
        if (exp != act)
        {
            std::cerr << "fail, exp: " << exp
                      << ", act: " << act << "\n";
        }
    }
}