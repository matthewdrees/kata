// LeetCode 58. Length of Last Word.

class Solution {
    func lengthOfLastWord(_ s: String) -> Int {
        if let lastWord = s.split(separator: " ").last {
            return lastWord.count
        }
        return 0
    }
}

struct TestCase {
    var s : String
    var exp : Int
}

let test_cases = [
    TestCase(s: "", exp: 0),
    TestCase(s: "a", exp: 1),
    TestCase(s: "a ", exp: 1),
    TestCase(s: " a", exp: 1),
    TestCase(s: "Hello World", exp: 5),
    TestCase(s: "   fly me   to   the moon  ", exp: 4),
    TestCase(s: "luffy is still joyboy", exp: 6),
]

var solution = Solution()
for tc in test_cases {
    let act = solution.lengthOfLastWord(tc.s)
    if tc.exp != act {
        print("Fail. s: '\(tc.s)', exp: \(tc.exp), act: \(act)")
    }
}