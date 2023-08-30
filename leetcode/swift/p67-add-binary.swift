// LeetCode 67, Add Binary.

class Solution {
    func addBinary(_ a: String, _ b: String) -> String {
        precondition(a.count > 0)
        precondition(b.count > 0)
        var longer : [Int]
        var shorter : [Int]
        if a.count < b.count {
            shorter = a.compactMap(\.wholeNumberValue)
            longer = b.compactMap(\.wholeNumberValue)
        } else {
            shorter = b.compactMap(\.wholeNumberValue)
            longer = a.compactMap(\.wholeNumberValue)
        }
        var carry = 0
        var lIndex = longer.count - 1
        for sVal in shorter.reversed() {
            let total = sVal + longer[lIndex] + carry
            let (q, r) = total.quotientAndRemainder(dividingBy: 2)
            carry = q
            longer[lIndex] = r
            lIndex -= 1
        }
        while carry != 0 && lIndex >= 0 {
            let total = longer[lIndex] + carry
            let (q, r) = total.quotientAndRemainder(dividingBy: 2)
            carry = q
            longer[lIndex] = r
            lIndex -= 1
        }
        if carry != 0 {
            longer.insert(1, at: 0)
        }
        return (longer.map{String($0)}).joined(separator: "")
    }
}

struct TestCase {
    var a : String
    var b : String
    var exp : String

    init(_ a:String, _ b: String, _ exp: String) {
        self.a = a
        self.b = b
        self.exp = exp
    }
}

let test_cases = [
    TestCase("0", "0", "0"),
    TestCase("1", "0", "1"),
    TestCase("0", "1", "1"),
    TestCase("1", "1", "10"),
    TestCase("1", "10", "11"),
    TestCase("1", "11", "100"),
    TestCase("1010", "1011", "10101"),
    TestCase("10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101", "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011",  "110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000"),
]

let solution = Solution()

for tc in test_cases {
    let act = solution.addBinary(tc.a, tc.b)
    if tc.exp != act {
        print("fail, a: \(tc.a), b: \(tc.b), exp: \(tc.exp), act: \(act)")
    }
}
