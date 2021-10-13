# LeetCode 49. Group Anagrams.
from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        d = {}
        for s in strs:
            key = "".join(sorted(s))
            if key in d:
                d[key].append(s)
            else:
                d[key] = [s]
        l = []
        for key, item in d.items():
            l.append(item)
        return l


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
