// LeetCode 2149. Rearrange Array Elements by Sign.

use std::vec::Vec;

pub struct Solution {}

impl Solution {
    pub fn rearrange_array(nums: Vec<i32>) -> Vec<i32> {
        let mut ans = nums.clone();
        let mut pi: usize = 0;
        let mut ni: usize = 1;
        for n in nums {
            if n >= 0 {
                ans[pi] = n;
                pi += 2;
            } else {
                ans[ni] = n;
                ni += 2;
            }
        }
        return ans;
    }
}

#[cfg(test)]
mod tests {

    #[test]
    fn test_rearrange_array() {
        use crate::solution::Solution;
        assert_eq!(
            vec![3, -2, 1, -5, 2, -4],
            Solution::rearrange_array(vec![3, 1, -2, -5, 2, -4]),
        );
        assert_eq!(vec![1, -1], Solution::rearrange_array(vec![-1, 1]),);
    }
}
