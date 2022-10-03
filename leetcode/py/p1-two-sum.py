from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        # value -> index mapping
        d = {}
        for x, n in enumerate(nums):
            ans = target - n
            if ans in d:
                return [d[ans], x]
            d[n] = x


if __name__ == "__main__":
    s = Solution()
    tests = (
        ([1, 1], 2, [0, 1]),
        ([2, 7], 9, [0, 1]),
        ([2, 7, 11, 15], 9, [0, 1]),
        ([2, 7, 11, 15], 13, [0, 2]),
        ([2, 7, 11, 15], 17, [0, 3]),
        ([2, 7, 11, 15], 18, [1, 2]),
        ([2, 7, 11, 15], 22, [1, 3]),
        ([2, 7, 11, 15], 26, [2, 3]),
    )
    for nums, target, exp in tests:
        ans = s.twoSum(nums, target)
        if exp != ans:
            print(f"FAIL. nums: {nums}, target: {target}, exp: {exp}, ans: {ans}")
