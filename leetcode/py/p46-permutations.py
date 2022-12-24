# LeetCode 46. Permutations.
from typing import List
import copy


def cycle6(l, nums):
    for _ in range(6):
        cycle5(l, nums)
        nums.append(nums.pop(-6))


def cycle5(l, nums):
    for _ in range(5):
        cycle4(l, nums)
        nums.append(nums.pop(-5))


def cycle4(l, nums):
    for _ in range(4):
        cycle3(l, nums)
        nums.append(nums.pop(-4))


def cycle3(l, nums):
    l.append(copy.deepcopy(nums))
    nums[-1], nums[-2] = nums[-2], nums[-1]
    l.append(copy.deepcopy(nums))
    nums.insert(-2, nums.pop())
    l.append(copy.deepcopy(nums))
    nums[-1], nums[-2] = nums[-2], nums[-1]
    l.append(copy.deepcopy(nums))
    nums.append(nums.pop(-3))
    l.append(copy.deepcopy(nums))
    nums[-1], nums[-2] = nums[-2], nums[-1]
    l.append(copy.deepcopy(nums))
    nums[-1], nums[-3] = nums[-3], nums[-1]


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        len_nums = len(nums)
        if len_nums == 1:
            return [nums]
        if len_nums == 2:
            return [nums, [nums[1], nums[0]]]

        l = []
        if len_nums == 3:
            cycle3(l, nums)
        elif len_nums == 4:
            cycle4(l, nums)
        elif len_nums == 5:
            cycle5(l, nums)
        elif len_nums == 6:
            cycle6(l, nums)
        return l


solution = Solution()
for x in range(1, 6):
    ans = solution.permute(list(range(x)))
    ans_t = tuple([tuple(x) for x in ans])
    print(f"len: {len(set(ans_t))}")
    print(f"{ans}")

ans = solution.permute(list(range(6)))
ans_t = tuple([tuple(x) for x in ans])
print(f"len: {len(set(ans_t))}")
