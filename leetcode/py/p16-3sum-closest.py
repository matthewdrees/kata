#  LeetCode problem 16. 3Sum Closest.
from typing import List
import itertools
import random


class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        """Find three integers in nums such that the sum is closest to target.

        Faster than 96% of leetcode submissions."""
        assert len(nums) >= 3
        nums.sort()
        smallest_3_sum = sum(nums[:3])
        smallest_negative_delta = target - smallest_3_sum
        if smallest_negative_delta <= 0:
            return smallest_3_sum
        largest_3_sum = sum(nums[-3:])
        smallest_positive_delta = largest_3_sum - target
        if smallest_positive_delta <= 0:
            return largest_3_sum
        for b in range(1, len(nums) - 1):
            a = 0
            c = len(nums) - 1
            nearest = nums[a] + nums[b] + nums[c]
            while True:
                if nearest < target:
                    delta = target - nearest
                    if delta < smallest_negative_delta:
                        smallest_negative_delta = delta
                        if delta == 0:
                            return target
                    nearest -= nums[a]
                    a += 1
                    if a == b:
                        break
                    nearest += nums[a]
                elif nearest > target:
                    delta = nearest - target
                    if delta < smallest_positive_delta:
                        smallest_positive_delta = delta
                        if delta == 0:
                            return target
                    nearest -= nums[c]
                    c -= 1
                    if b == c:
                        break
                    nearest += nums[c]
                else:
                    return target
        if smallest_negative_delta <= smallest_positive_delta:
            return target - smallest_negative_delta
        return target + smallest_positive_delta

    def threeSumClosest_terrible(self, nums: List[int], target: int) -> int:
        """Simplest algorithm to get it working. O(n^3) runtime complexity. Bad."""
        assert len(nums) >= 3
        smallest_delta = nums[0] + nums[1] + nums[2]
        print(f"target: {target}, smallest_delta: {smallest_delta}")
        closest_sum = smallest_delta
        for l in itertools.combinations(nums, 3):
            n = sum(l)
            delta = abs(n - target)
            if delta < smallest_delta:
                smallest_delta = delta
                print(f"target: {target}, smallest: {l}")
                closest_sum = n
        return closest_sum


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([1, 1, 2], 0, 4),
        ([-1, 2, 0], 0, 1),
        ([-1, 2, 1, -4], 1, 2),
        ([-3, -2, -5, 3, -4], -1, -2),
        ([100, -90, 37, -72, -80, 33, -19, 7, -6, 4], -40, -40),
        ([100, -90, 37, -72, -80, 33, -19, 7, -6, 4], 0, 1),
        ([100, -90, 37, -72, -80, 33, -19, 7, -6, 4], 1, 1),
        ([100, -90, 37, -72, -80, 33, -19, 7, -6, 4], 2, 1),
        ([100, -90, 37, -72, -80, 33, -19, 7, -6, 4], 3, 4),
    )
    for nums, target, exp in tests:
        ans = s.threeSumClosest(nums, target)
        if exp != ans:
            print(f"FAIL, nums: {nums}, target: {target}, exp: {exp}, ans: {ans}")

    # This took forever with the slow O(n^3) approach.
    # l = [random.randint(-1000, 1000) for x in range(600)]
    # print(s.threeSumClosest(l, 47))
