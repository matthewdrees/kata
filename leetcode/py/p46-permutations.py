# LeetCode 46. Permutations.
from typing import List
import copy


def permute_rec(nums, l, i):
    if i > 3:
        for _ in range(i):
            permute_rec(nums, l, i - 1)
            nums.append(nums.pop(-i))
    else:
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
        if len_nums >= 3:
            l = []
            permute_rec(nums, l, len_nums)
            return l
        if len_nums == 1:
            return [nums]
        if len_nums == 2:
            return [nums, [nums[1], nums[0]]]
        return []


solution = Solution()
for x in range(1, 6):
    ans = solution.permute(list(range(x)))
    ans_t = tuple([tuple(x) for x in ans])
    print(f"len: {len(set(ans_t))}")
    print(f"{ans}")

ans = solution.permute(list(range(6)))
ans_t = tuple([tuple(x) for x in ans])
print(f"len: {len(set(ans_t))}")
