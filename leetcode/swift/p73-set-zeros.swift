// LeetCode 73. Set zeros.

func set_col_zero(_ matrix: inout [[Int]], col: Int) {
    for y in matrix.indices {
        matrix[y][col] = 0;
    }
}

func is_first_col_zero(_ matrix: [[Int]]) -> Bool {
    for y in matrix.indices {
        if matrix[y][0] == 0 {
            return true
        }
    }
    return false
}

class Solution {
    func setZeroes(_ matrix: inout [[Int]]) {
        precondition(matrix.count > 0)
        let X = matrix[0].count
        precondition(X > 0)

        let first_col_is_zero = is_first_col_zero(matrix)

        for y in matrix.indices {
            if matrix[y].contains(0) {
                matrix[y][0] = 0;
            }
        }

        for x in 1..<X {
            for y in matrix.indices {
                if matrix[y][x] == 0 {
                    set_col_zero(&matrix, col: x)
                    break
                }
            }
        }

        for y in matrix.indices {
            if matrix[y][0] == 0 {
                for x in matrix[y].indices {
                    matrix[y][x] = 0
                }
            }
        }

        if first_col_is_zero {
            set_col_zero(&matrix, col: 0)
        }
    }
}

struct TestCase {
    var matrix : [[Int]]
    var exp : [[Int]]

    init(_ matrix : [[Int]], _ exp: [[Int]]) {
        self.matrix = matrix
        self.exp = exp
    }
}

let test_cases = [
    TestCase([[0]], [[0]]),
    TestCase([[1]], [[1]]),
    TestCase([[1, 1]], [[1, 1]]),
    TestCase([[0, 1]], [[0, 0]]),
    TestCase([[1, 0]], [[0, 0]]),
    TestCase([[1] , [ 1 ] ], [ [ 1 ], [ 1 ] ] ),
    TestCase( [ [ 0 ],
              [ 1 ] ],
            [ [ 0 ],
                [ 0 ] ] ),
    TestCase([ [ 1 ], [ 0 ] ], [ [ 0 ], [ 0 ] ] ),
    TestCase( [ [ 1, 1 ],
              [ 1, 1 ] ],
            [ [ 1, 1 ],
                [ 1, 1 ] ] ),
    TestCase( [ [ 0, 1 ],
              [ 1, 1 ] ],
            [ [ 0, 0 ],
                [ 0, 1 ] ] ),
    TestCase( [ [ 1, 0 ],
              [ 1, 1 ] ],
            [ [ 0, 0 ],
                [ 1, 0 ] ] ),
    TestCase([ [ 1, 1 ],
              [ 0, 1 ] ],
            [ [ 0, 1 ],
                [ 0, 0 ] ] ),
    TestCase([ [ 1, 1 ],
              [ 1, 0 ] ],
            [ [ 1, 0 ],
                [ 0, 0 ] ] ),
    TestCase([ [ 1, 1, 1 ],
              [ 1, 0, 1 ],
              [ 1, 1, 1 ] ],
            [ [ 1, 0, 1 ],
                [ 0, 0, 0 ],
                [ 1, 0, 1 ] ] ),
    TestCase([ [ 0, 1, 2, 0 ],
              [ 3, 4, 5, 2 ],
              [ 1, 3, 1, 5 ] ],
            [ [ 0, 0, 0, 0 ],
                [ 0, 4, 5, 0 ],
                [ 0, 3, 1, 0 ] ] ),
]

var solution = Solution()
for tc in test_cases {
    var act = tc.matrix
    solution.setZeroes(&act)
    if tc.exp != act {
        print("Fail. matrix: '\(tc.matrix)', exp: '\(tc.exp)', act: '\(act)'")
    }
}
