// LeetCode 60. Permutation Sequence.

func factorial(_ n: Int) -> Int
{
    var fact = 1
    for i in 1...n {
        fact = fact * i
    }
    return fact
}

class Solution {
    func getPermutation(_ n: Int, _ k: Int) -> String {
        var k_ = k - 1
        var a = Array("123456789")
        var ans = String()
        for i in (1 ..< n).reversed() {
            let div = factorial(i)
            let idx = k_ / div
            k_ = k_ % div
            ans.append(a.remove(at:idx))
        }
        ans.append(a[0])
        return ans
    }
}

struct TestCase {
    var n: Int
    var k: Int
    var exp: String
}

let test_cases = [
        TestCase(n: 1, k: 1, exp: "1" ),
        TestCase(n: 2, k: 1, exp: "12" ),
        TestCase(n: 2, k: 2, exp: "21" ),
        TestCase(n: 3, k: 1, exp: "123" ),
        TestCase(n: 3, k: 2, exp: "132" ),
        TestCase(n: 3, k: 3, exp: "213" ),
        TestCase(n: 3, k: 4, exp: "231" ),
        TestCase(n: 3, k: 5, exp: "312" ),
        TestCase(n: 3, k: 6, exp: "321" ),
        TestCase(n: 4, k: 1, exp: "1234" ),
        TestCase(n: 4, k: 2, exp: "1243" ),
        TestCase(n: 4, k: 9, exp: "2314" ),
        TestCase(n: 4, k: 24, exp: "4321" ),
        TestCase(n: 5, k: 1, exp: "12345" ),
        TestCase(n: 5, k: 120, exp: "54321" ),
        TestCase(n: 6, k: 1, exp: "123456" ),
        TestCase(n: 6, k: 720, exp: "654321" ),
        TestCase(n: 7, k: 1, exp: "1234567" ),
        TestCase(n: 7, k: 5040, exp: "7654321" ),
        TestCase(n: 8, k: 1, exp: "12345678" ),
        TestCase(n: 8, k: 40320, exp: "87654321" ),
        TestCase(n: 9, k: 1, exp: "123456789" ),
        TestCase(n: 9, k: 2, exp: "123456798" ),
        TestCase(n: 9, k: 362880, exp: "987654321" ),
]

let solution = Solution()
for tc in test_cases {
    let act = solution.getPermutation(tc.n, tc.k)
    if tc.exp != act {
        print("fail, n: \(tc.n), k: \(tc.k), exp: \(tc.exp), act: \(act)")
    }
}