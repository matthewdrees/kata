// LeetCode 1119. Remove Vowels from a String.

use std::collections::HashSet;

struct Solution {}

impl Solution {
    pub fn remove_vowels(mut s: String) -> String {
        let vowels = HashSet::from(['a', 'e', 'i', 'o', 'u']);
        s.retain(|x| !vowels.contains(&x));
        return s;
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
