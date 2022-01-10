# LeetCode 1710. Maximum Units on a Truck.
import copy
from typing import List


class Solution:
    def maximumUnits(self, boxTypes: List[List[int]], truckSize: int) -> int:
        boxTypes.sort(key=lambda x: x[1], reverse=True)
        totalUnits = 0
        for numberOfBoxes, numberOfUnitsPerBox in boxTypes:
            if numberOfBoxes >= truckSize:
                totalUnits += truckSize * numberOfUnitsPerBox
                return totalUnits
            totalUnits += numberOfBoxes * numberOfUnitsPerBox
            truckSize -= numberOfBoxes
        return totalUnits


if __name__ == "__main__":

    tests = (
        ([], 1, 0),
        ([[1, 3]], 1, 3),
        ([[2, 3]], 1, 3),
        ([[2, 3]], 10, 6),
        ([[1, 3], [2, 2], [3, 1]], 4, 8),
        ([[5, 10], [2, 5], [4, 7], [3, 9]], 10, 91),
    )
    solution = Solution()
    for boxTypes, truckSize, exp in tests:
        ans = solution.maximumUnits(copy.deepcopy(boxTypes), truckSize)
        if exp != ans:
            print(
                f"FAIL. boxTypes: {boxTypes}, truckSize: {truckSize}, exp: {exp}, ans: {ans}"
            )
