// LeetCode 1762. Buildings With an Ocean View.
#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> anagramMappings(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        std::vector<int> v = nums1;
        std::transform(v.begin(), v.end(), v.begin(), [&](const auto& n) {
            return static_cast<int>(std::find(nums2.begin(), nums2.end(), n) - nums2.begin());
        });
        return v;
    }
};

int main()
{
    struct TestCase {
        std::vector<int> nums1;
        std::vector<int> nums2;
        std::vector<int> exp;
    };
    const TestCase testCases[] = {
        { {}, {}, {} },
        { { 12, 28, 46, 32, 50 }, { 50, 12, 32, 46, 28 }, { 1, 4, 3, 2, 0 } },
        { { 84, 46 }, { 84, 46 }, { 0, 1 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.anagramMappings(tc.nums1, tc.nums2);
        if (tc.exp != ans) {
            std::cout << "FAIL. "
                      << "(nums1.size()): " << tc.nums1.size() << ")"
                      << ", exp size: " << tc.exp.size()
                      << ", ans size: " << ans.size() << "\n";
        }
    }
    return 0;
}
