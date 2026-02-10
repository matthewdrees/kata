from typing import List

class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        l = []
        oldrow = []
        for _ in range(numRows):
            newrow = [1] * (len(oldrow) + 1)
            for x in range(1, len(oldrow)):
                newrow[x] = oldrow[x-1] + oldrow[x]
            l.append(newrow)
            oldrow = newrow
        return l


tests = (
    (0, []),
    (1, [[1]]),
    (2, [[1], [1,1]]),
    (3, [[1], [1,1], [1,2,1]]),
    (4, [[1], [1,1], [1,2,1], [1,3,3,1]]),
    (5, [[1], [1,1], [1,2,1], [1,3,3,1], [1,4,6,4,1]]),
    (6, [[1], [1,1], [1,2,1], [1,3,3,1], [1,4,6,4,1], [1,5,10,10,5,1]]),
    (7, [[1], [1,1], [1,2,1], [1,3,3,1], [1,4,6,4,1], [1,5,10,10,5,1],[1,6,15,20,15,6,1]]),
)
s = Solution()
for numRows, exp in tests:
    ans = s.generate(numRows)
    if exp != ans:
        print(f'FAIL. numRows: {numRows}, exp: {exp}, ans: {ans}')
