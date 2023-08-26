// LeetCode 66, Plus One.

class Solution {
    func plusOne(_ digits: [Int]) -> [Int] {
        var digits2 = digits
        for i in (0..<digits2.count).reversed() {
            digits2[i] += 1
            if digits2[i] < 10 {
                return digits2
            }
            else {
                digits2[i] = 0
            }
        }
        digits2.insert(1, at: 0)
        return digits2
    }
}

struct TestCase {
    var digits: [Int]
    var exp: [Int]
}

let solution = Solution()

let test_cases = [
    TestCase(digits: [0], exp: [1]),
    TestCase(digits: [9], exp: [1, 0]),
    TestCase(digits: [9, 8], exp: [9, 9]),
    TestCase(digits: [8, 9], exp: [9, 0]),
    TestCase(digits: [9, 9], exp: [1, 0, 0]),
    TestCase(digits: [1,2,3], exp: [1, 2, 4]),
    TestCase(digits: [4,3,2,1], exp: [4,3,2,2]),
]

var soluion = Solution()
for tc in test_cases {
    let act = solution.plusOne(tc.digits)
    if tc.exp != act {
        print("Fail, s: \(tc.digits), exp: \(tc.exp), act: \(act)")
    }
}