// LeetCode 3. Longest Substring Without Repeating Characters.
use std::collections::HashSet;

struct Solution {}

impl Solution {
    pub fn length_of_longest_substring(s: &String) -> i32 {
        let mut longest = 0 as usize;
        let mut hs: HashSet<u8> = HashSet::new();
        let bytes = s.as_bytes();
        let mut x = 0 as usize;
        let mut y = 0 as usize;
        while y < bytes.len() {
            let by = bytes[y];
            if hs.contains(&by) {
                hs.remove(&bytes[x]);
                x += 1;
            } else {
                hs.insert(by);
                y += 1;
                let cur_len = y - x;
                if cur_len > longest {
                    longest = cur_len;
                }
            }
        }
        return longest as i32;
    }
}

fn main() {
    struct TestCase {
        s: String,
        exp: i32,
    }

    let test_cases = vec![
        TestCase {
            s: "halothere".to_string(),
            exp: 7,
        },
        TestCase {
            s: "abcabcbb".to_string(),
            exp: 3,
        },
        TestCase {
            s: "bbbbb".to_string(),
            exp: 1,
        },
        TestCase {
            s: "pwwkew".to_string(),
            exp: 3,
        },
        TestCase {
            s: " ".to_string(),
            exp: 1,
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::length_of_longest_substring(&tc.s);
        if tc.exp != act {
            println!("FAIL. s: {:?}, exp: {}, act: {}", tc.s, tc.exp, act);
        }
    }
}
