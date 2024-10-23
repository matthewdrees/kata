// LeetCode 1119. Remove Vowels from a String.
struct Solution {}

impl Solution {
    pub fn remove_vowels(s: String) -> String {
        let mut ret = String::with_capacity(s.len());
        for c in s.chars() {
            if c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' {
                ret.push(c);
            }
        }
        return ret;
    }
}

fn main() {
    struct TestCase {
        s: String,
        exp: String,
    }

    let test_cases = vec![
        TestCase {
            s: "leetcodeisacommunityforcoders".to_string(),
            exp: "ltcdscmmntyfrcdrs".to_string(),
        },
        TestCase {
            s: "aeiou".to_string(),
            exp: "".to_string(),
        },
        TestCase {
            s: "a".to_string(),
            exp: "".to_string(),
        },
        TestCase {
            s: "b".to_string(),
            exp: "b".to_string(),
        },
    ];
    for tc in test_cases {
        let act = Solution::remove_vowels(tc.s.clone());
        if tc.exp != act {
            println!("FAIL. s: {}, exp: {}, act: {}", tc.s, tc.exp, act);
        }
    }
}
