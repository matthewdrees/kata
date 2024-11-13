// LeetCode 300. Longest Increasing Subsequence.
pub struct Solution {}

impl Solution {
    pub fn length_of_lis(nums: Vec<i32>) -> i32 {
        let mut dp = Vec::new();
        for n in nums.into_iter() {
            let idx = dp.iter_mut().find(|&&mut x| n <= x);
            match idx {
                Some(x) => *x = n,
                None => dp.push(n),
            }
        }
        return dp.len() as i32;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_length_of_lis() {
        assert_eq!(4, Solution::length_of_lis(vec![10, 9, 2, 5, 3, 7, 101, 18]));
        assert_eq!(4, Solution::length_of_lis(vec![0, 1, 0, 3, 2, 3]));
        assert_eq!(1, Solution::length_of_lis(vec![7, 7, 7, 7, 7, 7, 7]));
        assert_eq!(2500, Solution::length_of_lis(Vec::from_iter(0..2500)));
    }
}
