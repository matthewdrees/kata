// LeetCode 198. House Robber.

pub struct Solution {}

impl Solution {
    pub fn rob(nums: &Vec<i32>) -> i32 {
        let mut largep = 0;
        let mut large = 0;
        for n in nums.into_iter() {
            let newlarge = std::cmp::max(n + largep, large);
            largep = large;
            large = newlarge;
        }
        return large;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rob() {
        let mut passed = true;
        struct TC {
            nums: Vec<i32>,
            exp: i32,
        }
        let test_cases = vec![
            TC { nums: vec![], exp: 0 },
            TC { nums: vec![0], exp: 0 },
            TC { nums: vec![1], exp: 1 },
            TC { nums: vec![1, 2, 3, 1], exp: 4 },
            TC { nums: vec![2, 7, 9, 3, 1], exp: 12 },
            TC { nums: vec![9, 1, 9, 1, 1], exp: 19 },
            TC { nums: vec![9, 1, 1, 9, 1], exp: 18 },
            TC { nums: vec![9, 1, 9, 1, 9], exp: 27 },
        ];

        for tc in test_cases.iter() {
            let act = Solution::rob(&tc.nums);
            if tc.exp != act {
                passed = false;
                eprintln!("(nums: {:?}), exp: {}, act: {}", tc.nums, tc.exp, act);
            }
        }
        assert!(passed);
    }
}
