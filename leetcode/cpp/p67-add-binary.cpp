// LeetCode 67. Add Binary.
#include <iostream>

class Solution {
public:
    std::string addBinary(std::string a, std::string b)
    {
        std::string ans(std::max(a.size(), b.size()), '0');
        auto ans_it = ans.rbegin();
        auto ait = a.rbegin();
        auto bit = b.rbegin();
        bool carry = false;
        while (ait != a.rend() || bit != b.rend()) {
            const auto a_val = ait == a.rend() ? '0' : *ait++;
            const auto b_val = bit == b.rend() ? '0' : *bit++;
            const int total = static_cast<int>(a_val == '1') + static_cast<int>(b_val == '1') + static_cast<int>(carry);
            if (total == 1 || total == 3) {
                *ans_it = '1';
            }
            carry = total >= 2;
            ++ans_it;
        }
        if (carry) {
            return "1" + ans;
        }
        return ans;
    }

    // Nope, this didn't work.
    std::string addBinary2(std::string a, std::string b)
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
        { "1", "10", "11" },
        { "11", "1", "100" },
        { "1", "11", "100" },
        { "0", "110", "110" },
        { "1010", "1011", "10101" },
        { "1011", "1010", "10101" },
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
