// LeetCode 43. Multiply Strings.

use std::vec::Vec;

fn multiply1(num: &Vec<u8>, x: u8, stage_num: usize, v: &mut Vec<u8>) {
    let mut carry = 0;
    let mut i = stage_num;
    for n in num {
        let val = *n * x + v[i] + carry;
        carry = val / 10;
        v[i] = val % 10;
        i += 1;
    }
    while carry != 0 {
        let val = v[i] + carry;
        carry = val / 10;
        v[i] = val % 10;
        i += 1;
    }
}

struct Solution {}

impl Solution {
    pub fn multiply(num1: String, num2: String) -> String {
        if num1 == "0" {
            return num1;
        }
        if num2 == "0" {
            return num2;
        }
        let mut v: Vec<u8> = Vec::new();
        v.resize_with(num1.len() + num2.len(), Default::default);
        let mut stage_num: usize = 0;
        let mut n2 = num2.as_bytes().to_vec();
        n2.reverse();
        for x in &mut n2 {
            *x -= 48;
        }
        for n1 in num1.as_bytes().iter().rev() {
            multiply1(&n2, n1 - 48, stage_num, &mut v);
            stage_num += 1;
        }
        if v.last() == Some(&0) {
            v.truncate(v.len() - 1);
        }
        v.reverse();
        for x in &mut v {
            *x += 48;
        }
        return String::from_utf8(v).unwrap();
    }
}
fn test_multiply1() {
    struct TestCase {
        n: Vec<u8>,
        x: u8,
        stage_num: usize,
        v: Vec<u8>,
        exp: Vec<u8>,
    }

    let test_cases = vec![
        TestCase {
            n: vec![0, 0],
            x: 0,
            stage_num: 0,
            v: vec![0, 0],
            exp: vec![0, 0],
        },
        TestCase {
            n: vec![1, 0],
            x: 3,
            stage_num: 0,
            v: vec![0, 0],
            exp: vec![3, 0],
        },
        TestCase {
            n: vec![1, 0],
            x: 3,
            stage_num: 1,
            v: vec![0, 0, 0],
            exp: vec![0, 3, 0],
        },
        TestCase {
            n: vec![1, 1],
            x: 3,
            stage_num: 0,
            v: vec![1, 0],
            exp: vec![4, 3],
        },
        TestCase {
            n: vec![1, 1],
            x: 3,
            stage_num: 0,
            v: vec![1, 0],
            exp: vec![4, 3],
        },
        TestCase {
            n: vec![1, 5],
            x: 3,
            stage_num: 0,
            v: vec![1, 0, 0],
            exp: vec![4, 5, 1],
        },
        TestCase {
            n: vec![3, 2, 1],
            x: 4,
            stage_num: 2,
            v: vec![8, 8, 8, 6, 0, 0],
            exp: vec![8, 8, 0, 6, 5, 0],
        },
    ];

    for tc in test_cases.iter() {
        let mut act = tc.v.clone();
        multiply1(&tc.n, tc.x, tc.stage_num, &mut act);
        if tc.exp != act {
            println!(
                "FAIL. n: {:?}, x: {}, stage_num: {}, v: {:?}, exp: {:?}, act: {:?}",
                tc.n, tc.x, tc.stage_num, tc.v, tc.exp, act
            );
        }
    }
}

fn test_multiply() {
    struct TestCase {
        num1: String,
        num2: String,
        exp: String,
    }

    let test_cases = vec![
        TestCase {
            num1: "2".to_string(),
            num2: "3".to_string(),
            exp: "6".to_string(),
        },
        TestCase {
            num1: "123".to_string(),
            num2: "456".to_string(),
            exp: "56088".to_string(),
        },
        TestCase {
            num1: "0".to_string(),
            num2: "456".to_string(),
            exp: "0".to_string(),
        },
        TestCase {
            num1: "123".to_string(),
            num2: "0".to_string(),
            exp: "0".to_string(),
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::multiply(tc.num1.clone(), tc.num2.clone());
        if tc.exp != act {
            println!(
                "FAIL. num1: {}, num2: {}, exp: {}, act: {}",
                tc.num1, tc.num2, tc.exp, act
            );
        }
    }
}

fn main() {
    test_multiply1();
    test_multiply();
}
