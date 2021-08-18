# LeetCode problem 18. 4Sum.

from typing import List
import bisect
import itertools
import random


class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nlen = len(nums)
        if len(nums) < 4:
            return []
        nums.sort()
        ans = []
        for a in range(nlen - 3):
            if target > nums[a] + sum(nums[-3:]):
                continue
            if target < sum(nums[a : a + 4]):
                return ans
            for b in range(a + 1, nlen - 2):
                c = b + 1
                d = nlen - 1
                if target > nums[a] + nums[b] + nums[d - 1] + nums[d]:
                    continue
                if target < nums[a] + sum(nums[b : b + 3]):
                    break
                while c < d:
                    grr = nums[a] + nums[b] + nums[c] + nums[d]
                    if grr < target:
                        c += 1
                    elif grr > target:
                        d -= 1
                    else:
                        l = [nums[a], nums[b], nums[c], nums[d]]
                        if l not in ans:
                            ans.append(l)
                            ans.sort()
                        c += 1
        return ans

    def fourSum_slow(self, nums: List[int], target: int) -> List[List[int]]:
        """Simplest algorithm to get it working. O(n^4) runtime complexity. Bad."""
        if len(nums) < 4:
            return []
        ans = set()
        for t in itertools.combinations(nums, 4):
            if sum(t) == target:
                ans.add(tuple(sorted(t)))
        return sorted([list(t) for t in ans])


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], 0, []),
        ([0], 0, []),
        ([0, 0], 0, []),
        ([0, 0, 0], 0, []),
        ([0, 0, 0, 0], 0, [[0, 0, 0, 0]]),
        ([0, 0, 0, 0, 0], 0, [[0, 0, 0, 0]]),
        ([2, 2, 2, 2, 2], 8, [[2, 2, 2, 2]]),
        ([1, 0, -1, 0, -2, 2], 0, [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]),
        ([-5, 5, 4, -3, 0, 0, 4, -2], 4, [[-5, 0, 4, 5], [-3, -2, 4, 5]]),
    )
    for nums, target, exp in tests:
        ans = s.fourSum(nums, target)
        if exp != ans:
            print(f"FAIL, nums: {nums}, target: {target}, exp: {exp}, ans: {ans}")

    for nums_len in range(90):
        nums = [random.randint(-100, 100) for x in range(nums_len)]
        target = random.randint(-100, 100)
        exp = s.fourSum_slow(nums, target)
        ans = s.fourSum(nums, target)
        if exp != ans:
            print(f"FAIL, nums: {nums}, target: {target}, exp: {exp}, ans: {ans}")
            break

    # Speed test
    nums = [random.randint(-1000000000, 1000000000) for x in range(200)]
    print(s.fourSum(nums, 47))
