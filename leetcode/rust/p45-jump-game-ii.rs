// LeetCode 45. Jump Game II.

use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn jump(nums: Vec<i32>) -> i32 {
        let mut ans: i32 = 0;
        let mut farthest: usize = 0;
        let mut end: usize = 0;
        for (i, n) in nums[0..nums.len() - 1].into_iter().enumerate() {
            farthest = std::cmp::max(farthest, i + *n as usize);
            if farthest >= nums.len() - 1 {
                ans += 1;
                break;
            }
            if i == end {
                ans += 1;
                end = farthest;
            }
        }
        return ans;
    }
}

fn main() {
    struct TestCase {
        nums: Vec<i32>,
        exp: i32,
    }

    let test_cases = vec![
        TestCase {
            nums: vec![5],
            exp: 0,
        },
        TestCase {
            nums: vec![1, 1],
            exp: 1,
        },
        TestCase {
            nums: vec![1, 0],
            exp: 1,
        },
        TestCase {
            nums: vec![1, 1, 7],
            exp: 2,
        },
        TestCase {
            nums: vec![2, 1, 7],
            exp: 1,
        },
        TestCase {
            nums: vec![2, 3, 1],
            exp: 1,
        },
        TestCase {
            nums: vec![2, 3, 1, 1, 4],
            exp: 2,
        },
        TestCase {
            nums: vec![2, 3, 0, 1, 4],
            exp: 2,
        },
        TestCase {
            nums: vec![5, 0, 0, 0, 0],
            exp: 1,
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::jump(tc.nums.clone());
        if tc.exp != act {
            println!("FAIL. nums: {:?}, exp: {}, act: {}", tc.nums, tc.exp, act);
        }
    }
}
