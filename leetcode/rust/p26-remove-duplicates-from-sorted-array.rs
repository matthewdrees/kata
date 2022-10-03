// LeetCode 26. Remove Duplicates from Sorted Array.
use std::convert::TryFrom;
use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        let mut k = 0;
        for i in 1..nums.len() {
            if nums[i] != nums[k] {
                k += 1;
                nums[k] = nums[i];
            }
        }
        return i32::try_from(k + 1).expect("Bad usize -> i32 conversion");
    }
}

fn main() {
    struct TestCase {
        nums: Vec<i32>,
        exp: Vec<i32>,
    }

    let mut test_cases = Vec::<TestCase>::new();
    test_cases.push(TestCase {
        nums: vec![1, 1, 2],
        exp: vec![1, 2],
    });
    test_cases.push(TestCase {
        nums: vec![0, 0, 1, 1, 1, 2, 2, 3, 3, 4],
        exp: vec![0, 1, 2, 3, 4],
    });

    for tc in test_cases.iter() {
        let mut act = tc.nums.clone();
        let k = Solution::remove_duplicates(&mut act);
        if tc.exp != act[..usize::try_from(k).expect("Bad i32->usize conversion")] {
            println!(
                "FAIL. nums: {:?}, exp: {:?}, act: {:?}, k: {}",
                tc.nums, tc.exp, act, k
            );
        }
    }
}
