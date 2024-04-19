// LeetCode 219. Contains Duplicate II.
use std::collections::HashMap;
use std::vec::Vec;

pub struct Solution {}

impl Solution {
    pub fn contains_nearby_duplicate(nums: Vec<i32>, k: i32) -> bool {
        let k = k as usize;
        let mut hm = HashMap::<i32, usize>::new();
        for (i, n) in nums.into_iter().enumerate() {
            if let Some(prev_i) = hm.get(&n) {
                if i - prev_i <= k {
                    return true;
                }
            }
            hm.insert(n, i);
        }
        return false;
    }
}

#[cfg(test)]
mod tests {

    #[test]
    fn test_contains_nearby_duplicate() {
        use crate::solution::Solution;
        assert_eq!(false, Solution::contains_nearby_duplicate(vec![1], 0));
        assert_eq!(true, Solution::contains_nearby_duplicate(vec![1,2,3,1], 3));
        assert_eq!(true, Solution::contains_nearby_duplicate(vec![1,0,1,1], 1));
        assert_eq!(false, Solution::contains_nearby_duplicate(vec![1,2,3,1,2,3], 2));
    }
}
