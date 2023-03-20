// LeetCode 55. Jump Game.

use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn can_jump(nums: Vec<i32>) -> bool {
        assert!(nums.len() > 0);
        let mut carry = nums[0];
        for n in nums[1..].into_iter() {
            if carry == 0 {
                return false;
            }
            carry = std::cmp::max(carry - 1, *n)
        }
        return true;
    }
}

fn main() {
    struct TestCase {
        nums: Vec<i32>,
        exp: bool,
    }

    let test_cases = vec![
        TestCase {
            nums: vec![2, 3, 1, 1, 4],
            exp: true,
        },
        TestCase {
            nums: vec![3, 2, 1, 0, 4],
            exp: false,
        },
        TestCase {
            nums: vec![0],
            exp: true,
        },
        TestCase {
            nums: vec![1],
            exp: true,
        },
        TestCase {
            nums: vec![1, 0],
            exp: true,
        },
        TestCase {
            nums: vec![0, 1],
            exp: false,
        },
        TestCase {
            nums: vec![5, 0, 0, 0, 0, 0],
            exp: true,
        },
        TestCase {
            nums: vec![5, 0, 0, 0, 0, 0, 1],
            exp: false,
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::can_jump(tc.nums.clone());
        if tc.exp != act {
            println!("FAIL. nums: {:?}, exp: {}, act: {}", tc.nums, tc.exp, act);
        }
    }
}
