struct Solution {}

impl Solution {
    pub fn plus_one(digits: Vec<i32>) -> Vec<i32> {
        let mut digits = digits;
        for i in (0..digits.len()).rev() {
            digits[i] += 1;
            if digits[i] < 10 {
                return digits;
            }
            digits[i] = 0;
        }
        digits.insert(0, 1);
        return digits;
    }
}

fn main() {
    struct TestCase {
        digits: Vec<i32>,
        exp: Vec<i32>,
    }

    let test_cases = vec![
        TestCase {
            digits: vec![0],
            exp: vec![1],
        },
        TestCase {
            digits: vec![9],
            exp: vec![1, 0],
        },
        TestCase {
            digits: vec![8, 9],
            exp: vec![9, 0],
        },
        TestCase {
            digits: vec![9, 8],
            exp: vec![9, 9],
        },
        TestCase {
            digits: vec![9, 9],
            exp: vec![1, 0, 0],
        },
        TestCase {
            digits: vec![9, 9],
            exp: vec![1, 0, 0],
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::plus_one(tc.digits.clone());
        if tc.exp != act {
            println!(
                "Fail, digits: {:?}, exp: {:?}, act: {:?}",
                tc.digits, tc.exp, act
            )
        }
    }
}
