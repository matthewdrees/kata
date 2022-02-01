// LeetCode 1507. Reformat Date.
#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <unordered_map>

const std::unordered_map<std::string, std::string> date_map = {
    { "Jan", "01" },
    { "Feb", "02" },
    { "Mar", "03" },
    { "Apr", "04" },
    { "May", "05" },
    { "Jun", "06" },
    { "Jul", "07" },
    { "Aug", "08" },
    { "Sep", "09" },
    { "Oct", "10" },
    { "Nov", "11" },
    { "Dec", "12" },
};

class Solution {
public:
    std::string reformatDate(const std::string date)
    {
        const auto first_space = std::find(begin(date), end(date), ' ');
        assert(first_space != end(date));
        const auto second_space = std::find(first_space + 1, end(date), ' ');
        assert(std::distance(second_space, end(date)) == 5);
        //                      0123456789
        std::string new_date = "yyyy-mm-0d";

        // copy the year
        std::copy(second_space + 1, end(date), begin(new_date));

        // copy the month
        const std::string month(first_space + 1, second_space);
        const auto new_month = date_map.find(month);
        assert(new_month != date_map.end());
        new_date.replace(5, 2, new_month->second);

        // copy the day
        if (isdigit(date[1])) {
            new_date[8] = date[0];
            new_date[9] = date[1];
        } else {
            new_date[9] = date[0];
        }
        return new_date;
    }
};

int main()
{
    struct TestCase {
        std::string date;
        std::string exp;
    };
    const TestCase testCases[] = {
        { "20th Oct 2052", "2052-10-20" },
        { "6th Jun 1933", "1933-06-06" },
        { "26th May 1960", "1960-05-26" },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.reformatDate(tc.date);
        if (tc.exp != ans) {
            std::cout << "FAIL. " << __FUNCTION__ << "(date: " << tc.date << ")"
                      << ", exp: " << tc.exp
                      << ", ans: " << ans
                      << "\n";
        }
    }
    return 0;
}
