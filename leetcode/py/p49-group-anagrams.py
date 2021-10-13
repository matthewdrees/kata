# LeetCode 49. Group Anagrams.
from typing import List
import collections


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        d = collections.defaultdict(list)
        for s in strs:
            d["".join(sorted(s))].append(s)
        return list(d.values())


if __name__ == "__main__":

    solution = Solution()
    tests = (
        (
            ["eat", "tea", "tan", "ate", "nat", "bat"],
            [["eat", "tea", "ate"], ["tan", "nat"], ["bat"]],
        ),
        ([""], [[""]]),
        (["a"], [["a"]]),
    )

    for test in tests:
        strs = test[0]
        exp = test[1]
        ans = solution.groupAnagrams(strs)
        if exp != ans:
            print(f"FAIL. strs: {strs}, exp: {exp}, ans: {ans}")
