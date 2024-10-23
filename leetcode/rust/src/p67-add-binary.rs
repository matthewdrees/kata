use std::cmp;

struct Solution {}

impl Solution {
    pub fn add_binary(a: String, b: String) -> String {
        let mut ans = String::with_capacity(cmp::max(a.len(), b.len()));
        let mut ait = a.chars().rev();
        let mut bit = b.chars().rev();
        let mut carry = 0;

        loop {
            let mut do_break = false;
            let mut total = carry;
            match ait.next() {
                Some(c) => {
                    if c == '1' {
                        total += 1;
                    }
                }
                None => do_break = true,
            }
            match bit.next() {
                Some(c) => {
                    if c == '1' {
                        total += 1;
                    }
                }
                None => {
                    if do_break {
                        break;
                    }
                }
            }
            if total == 1 || total == 3 {
                ans.push('1');
            } else {
                ans.push('0');
            }
            if total >= 2 {
                carry = 1;
            } else {
                carry = 0;
            }
        }

        if carry > 0 {
            ans.push('1');
        }
        return ans.chars().rev().collect::<String>();
    }
}

fn main() {
    struct TestCase {
        a: String,
        b: String,
        exp: String,
    }
    let test_cases = vec![
        TestCase {
            a: "0".to_string(),
            b: "0".to_string(),
            exp: "0".to_string(),
        },
        TestCase {
            a: "1".to_string(),
            b: "0".to_string(),
            exp: "1".to_string(),
        },
        TestCase {
            a: "1".to_string(),
            b: "1".to_string(),
            exp: "10".to_string(),
        },
        TestCase {
            a: "10".to_string(),
            b: "1".to_string(),
            exp: "11".to_string(),
        },
        TestCase {
            a: "1".to_string(),
            b: "10".to_string(),
            exp: "11".to_string(),
        },
        TestCase {
            a: "11".to_string(),
            b: "1".to_string(),
            exp: "100".to_string(),
        },
        TestCase {
            a: "1".to_string(),
            b: "11".to_string(),
            exp: "100".to_string(),
        },
        TestCase {
            a: "0".to_string(),
            b: "110".to_string(),
            exp: "110".to_string(),
        },
        TestCase {
            a: "1010".to_string(),
            b: "1011".to_string(),
            exp: "10101".to_string(),
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::add_binary(tc.a.clone(), tc.b.clone());
        if tc.exp != act {
            println!(
                "Fail, a: {:?}, b: {:?}, exp: {:?}, act: {:?}",
                tc.a, tc.b, tc.exp, act
            );
        }
    }
}
