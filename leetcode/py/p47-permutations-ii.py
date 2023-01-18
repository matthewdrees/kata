# LeetCode 47. Permutations II.

from typing import List


class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        len_nums = len(nums)
        if len_nums == 0:
            return []
        if len_nums == 1:
            return [nums]
        nums.sort()
        permutations = [nums.copy()]
        if len_nums == 2:
            if nums[0] != nums[1]:
                permutations.append([nums[1], nums[0]])
            return permutations
        while True:
            i1 = len_nums - 1
            i2 = len_nums - 2
            if nums[i2] < nums[i1]:
                nums[i1], nums[i2] = nums[i2], nums[i1]
                permutations.append(nums.copy())
            i3 = len_nums - 3
            if nums[i3] < nums[i2]:
                tmp = nums[i1]
                if nums[i3] < nums[i1]:
                    # Rotate right
                    nums[i1] = nums[i2]
                    nums[i2] = nums[i3]
                    nums[i3] = tmp
                else:
                    # Rotate left
                    nums[i1] = nums[i3]
                    nums[i3] = nums[i2]
                    nums[i2] = tmp
                permutations.append(nums.copy())
                continue

            do_continue = False
            for i in range(len_nums - 4, -1, -1):
                n1 = nums[i]
                n2 = nums[i + 1]
                if n1 < n2:
                    j = len_nums - 1
                    while j >= i + 1 and n1 >= nums[j]:
                        j -= 1
                    nums[i], nums[j] = nums[j], nums[i]
                    # reverse
                    k = i + 1
                    l = len_nums - 1
                    while k < l:
                        nums[k], nums[l] = nums[l], nums[k]
                        k += 1
                        l -= 1
                    permutations.append(nums.copy())
                    do_continue = True
                    break
            if do_continue:
                continue
            break
        return permutations


test_cases = (
    ([2], [[2]]),
    ([1, 1], [[1, 1]]),
    ([1, 2], [[1, 2], [2, 1]]),
    ([2, 1], [[1, 2], [2, 1]]),
    ([1, 1, 2], [[1, 1, 2], [1, 2, 1], [2, 1, 1]]),
    (
        [1, 1, 2, 3],
        [
            [1, 1, 2, 3],
            [1, 1, 3, 2],
            [1, 2, 1, 3],
            [1, 2, 3, 1],
            [1, 3, 1, 2],
            [1, 3, 2, 1],
            [2, 1, 1, 3],
            [2, 1, 3, 1],
            [2, 3, 1, 1],
            [3, 1, 1, 2],
            [3, 1, 2, 1],
            [3, 2, 1, 1],
        ],
    ),
)

solution = Solution()
for nums, exp in test_cases:
    nums_copy = list(nums)
    act = solution.permuteUnique(nums)
    if exp != act:
        print(f"FAIL. nums: {nums_copy}, exp: {exp}, act: {act}")
