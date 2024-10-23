// LeetCode 46. Permutations.
use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
        return Solution::permute2(&nums);
    }
    pub fn permute2(nums: &[i32]) -> Vec<Vec<i32>> {
        if nums.len() == 1 {
            return vec![nums.to_vec()];
        }
        let permuted = Solution::permute2(&nums[1..]);
        let mut rv = Vec::new();
        for p in permuted {
            for i in 0..p.len() + 1 {
                let mut c_p: Vec<i32> = p.clone();
                c_p.insert(i, nums[0]);
                rv.push(c_p);
            }
        }
        return rv;
    }
}

fn main() {
    println!("{:?}", Solution::permute(vec![0]));
    println!("{:?}", Solution::permute(vec![0, 1]));
    println!("{:?}", Solution::permute(vec![0, 1, 2]));
    println!("{:?}", Solution::permute(vec![0, 1, 2, 3]));
}
