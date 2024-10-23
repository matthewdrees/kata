struct Solution {}

impl Solution {
    pub fn length_of_last_word(s: String) -> i32 {
        let s2 = s.trim_end();
        match s2.rfind(' ') {
            Some(i) => return (s2.len() - i - 1) as i32,
            None => return s2.len() as i32,
        }
    }
}

fn main() {
    struct TestCase {
        s: String,
        exp: i32,
    }
    let test_cases = vec![
        TestCase {
            s: "".to_string(),
            exp: 0,
        },
        TestCase {
            s: "a".to_string(),
            exp: 1,
        },
        TestCase {
            s: "a ".to_string(),
            exp: 1,
        },
        TestCase {
            s: " a".to_string(),
            exp: 1,
        },
        TestCase {
            s: "Hello World".to_string(),
            exp: 5,
        },
        TestCase {
            s: "   Hello World   ".to_string(),
            exp: 5,
        },
        TestCase {
            s: "there".to_string(),
            exp: 5,
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::length_of_last_word(tc.s.clone());
        if tc.exp != act {
            println!("Fail, s: {:?}, exp: {:?}, act: {:?}", tc.s, tc.exp, act);
        }
    }
}
