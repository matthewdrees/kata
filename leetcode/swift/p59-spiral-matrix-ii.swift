// LeetCode 59, Spiral Matrix II.

class Solution {
    func generateMatrix(_ n: Int) -> [[Int]] {
        assert(n >= 1 && n <= 20)
        var matrix = Array(repeating: Array(repeating: 0, count: n), count: n)
        var num = 1
        var dim0 = 0
        var dim1 = n
        while true {
            for x in dim0 ..< dim1 {
                matrix[dim0][x] = num
                num += 1
            }
            dim1 -= 1
            if dim0 == dim1 {
                break
            }
            for y in dim0 + 1 ..< dim1 {
                matrix[y][dim1] = num
                num += 1
            }
            for x in stride(from:dim1, to: dim0, by: -1) {
                matrix[dim1][x] = num
                num += 1
            }
            for y in stride(from:dim1, to: dim0, by: -1) {
                matrix[y][dim0] = num
                num += 1
            }
            dim0 += 1
            if dim0 == dim1 {
                break
            }
        }
        return matrix
    }
}

struct TestCase {
    var n : Int
    var exp : [[Int]]
}

let test_cases = [
    TestCase(n: 1, exp: [[1]]),
    TestCase(n: 2, exp: [[1, 2], [4, 3]]),
    TestCase(n: 3, exp: [[1,2,3], [8, 9, 4], [7, 6, 5]]),
    TestCase(n: 4, exp:  [[1,2,3, 4],
         [12, 13, 14, 5],
         [11, 16, 15, 6],
         [10, 9, 8, 7]]),
]

let solution = Solution()
for tc in test_cases {
    let act = solution.generateMatrix(tc.n)
    if tc.exp != act {
        print("Fail. s: '\(tc.n)', exp: \(tc.exp), act: \(act)")
    }
}