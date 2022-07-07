# LeetCode 760. Find Anagram Mappings
from typing import List


class Solution:
    def anagramMappings(self, nums1: List[int], nums2: List[int]) -> List[int]:
        d = {}
        for i, n in enumerate(nums2):
            d[n] = i
        l = [0] * len(nums1)
        for x in range(len(nums1)):
            l[x] = d[nums1[x]]
        return l


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], [], []),
        ([12, 28, 46, 32, 50], [50, 12, 32, 46, 28], [1, 4, 3, 2, 0]),
        ([84, 46], [84, 46], [0, 1]),
    )

    for test in tests:

        nums1 = test[0]
        nums2 = test[1]
        exp = test[2]
        ans = s.anagramMappings(nums1, nums2)
        if exp != ans:
            print(f"FAIL. nums1: {nums1}, nums2: {nums2}, exp: {exp}, ans: {ans}")
