// LeetCode 62. Unique Paths.

class Solution {
    func uniquePaths(_ m: Int, _ n: Int) -> Int {
        assert(m >= 1 && m <= 100);
        assert(n >= 1 && n <= 100);
        let X = max(m, n)
        let Y = min(m, n)
        var a = Array(repeating: 1, count: X)
        for _ in 1..<Y {
            for x in 1..<X {
                a[x] = a[x-1] + a[x]
            }
        }
        return a.last!
    }
}

struct TestCase {
    var m: Int
    var n: Int
    var exp: Int

    init(_ m:Int, _ n: Int, _ exp: Int) {
        self.m = m
        self.n = n
        self.exp = exp
    }
}

let testCases = [
    TestCase( 1, 1, 1 ),
    TestCase( 1, 2, 1 ),
    TestCase( 2, 1, 1 ),
    TestCase( 2, 2, 2 ),
    TestCase( 2, 3, 3 ),
    TestCase( 3, 2, 3 ),
    TestCase( 3, 3, 6 ),
    TestCase( 4, 4, 20 ),
    TestCase( 3, 7, 28 ),
    TestCase( 7, 3, 28 ),
    TestCase( 15, 21, 1391975640 ),
    TestCase( 16, 20, 1855967520 ),
    TestCase( 17, 18, 1166803110 ),
]

var solution = Solution()
for tc in testCases {
    let act = solution.uniquePaths(tc.m, tc.n)
    if tc.exp != act {
        print("Fail, m: \(tc.m), n: \(tc.n), exp: \(tc.exp), act: \(act)")
    }
}