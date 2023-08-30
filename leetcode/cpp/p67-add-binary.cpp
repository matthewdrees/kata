// LeetCode 67. Add Binary.
#include <iostream>

class Solution {
public:
    std::string addBinary(std::string a, std::string b)
    {
        return std::to_string(std::stoi(a, nullptr, 2) + std::stoi(b, nullptr, 2));
    }
};

int main()
{
    struct TestCase {
        std::string a;
        std::string b;
        std::string exp;
    };

    TestCase test_cases[] = {
        { "0", "0", "0" },
        { "0", "1", "1" },
        { "1", "0", "1" },
        { "1", "1", "10" },
        { "10", "1", "11" },
        { "11", "1", "100" },
        { "1010", "1011", "10101" },
    };
    Solution solution;
    for (auto& tc : test_cases) {
        const auto act = solution.addBinary(tc.a, tc.b);
        if (tc.exp != act) {
            std::cerr << "fail, a: " << tc.a
                      << ", b: " << tc.b
                      << ", exp: " << tc.exp
                      << ", act: " << act
                      << "\n";
        }
    }
}
