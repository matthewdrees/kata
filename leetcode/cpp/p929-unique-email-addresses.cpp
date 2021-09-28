// LeetCode 929.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

class Solution {
public:
    int numUniqueEmails(const std::vector<std::string>& emails)
    {
        std::unordered_set<std::string> unique_emails;
        for (auto email : emails) {
            // Get location of '@'.
            const auto at_it = std::find(email.begin(), email.end(), '@');

            // Get end of local_name
            const auto local_name_end = std::find(email.begin(), at_it, '+');

            // Remove any '.' characters and optional '+...' characters.
            email.erase(std::remove(email.begin(), local_name_end, '.'), at_it);

            unique_emails.insert(std::move(email));
        }
        return static_cast<int>(unique_emails.size());
    }
};

template <typename T>
std::string to_string(const std::vector<T>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto e : v) {
        oss << e << ',';
    }
    oss << "\b}";
    return oss.str();
}

int main()
{
    struct TestCase {
        std::vector<std::string> emails;
        int expected;
    };
    TestCase testCases[] = {
        { {}, 0 },
        { { "a@a.com" }, 1 },
        { { "test.email+alex@leetcode.com", "test.e.mail+bob.cathy@leetcode.com", "testemail+david@lee.tcode.com" }, 2 },
        { { "a@leetcode.com", "b@leetcode.com", "c@leetcode.com" }, 3 },
    };
    Solution s;
    for (const auto& tc : testCases) {
        const auto actual = s.numUniqueEmails(tc.emails);
        if (tc.expected != actual) {
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(emails: " << to_string(tc.emails) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual
                      << "\n";
        }
    }
    return 0;
}
