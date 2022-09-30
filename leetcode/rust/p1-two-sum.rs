// LeetCode 1. Two Sum.
use std::collections::HashMap;
use std::convert::TryFrom;
use std::vec::Vec;

struct Solution {}
impl Solution {
    pub fn two_sum(nums: &Vec<i32>, target: i32) -> Vec<i32> {
        let mut hm: HashMap<i32, i32> = HashMap::new();

        for (pos, n) in nums.iter().enumerate() {
            let ans = target - n;
            if hm.contains_key(&ans) {
                return vec![
                    hm[&ans],
                    i32::try_from(pos).expect("Bad usize -> i32 conversion"),
                ];
            }
            hm.insert(*n, i32::try_from(pos).expect("Bad usize -> i32 conversion"));
        }
        return vec![0, 0];
    }
}

fn main() {
    struct TestCase {
        nums: Vec<i32>,
        target: i32,
        exp: Vec<i32>,
    }

    let mut test_cases = Vec::<TestCase>::new();
    test_cases.push(TestCase {
        nums: vec![2, 7, 11, 15],
        target: 9,
        exp: vec![0, 1],
    });
    test_cases.push(TestCase {
        nums: vec![3, 2, 4],
        target: 6,
        exp: vec![1, 2],
    });
    test_cases.push(TestCase {
        nums: vec![3, 3],
        target: 6,
        exp: vec![0, 1],
    });

    for tc in test_cases.iter() {
        let act = Solution::two_sum(&tc.nums, tc.target);
        if tc.exp != act {
            println!(
                "FAIL. nums: {:?}, target: {}, exp: {:?}, act: {:?}",
                tc.nums, tc.target, tc.exp, act
            );
        }
    }
}
