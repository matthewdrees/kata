// LeetCode 75. Sort Colors.

pub struct Solution {}

impl Solution {
    pub fn sort_colors(nums: &mut Vec<i32>) {
        if nums.is_empty() {
            return;
        }
        let mut i: usize = 0;
        let mut k = nums.len();
        while i < k && nums[i] == 0 {
            i += 1;
        }
        while k > 0 && nums[k - 1] == 2 {
            k -= 1;
        }
        let mut j = i;
        while j < k {
            match nums[j] {
                0 => {
                    nums.swap(i, j);
                    i += 1;
                    j += 1;
                }
                1 => {
                    j += 1;
                }
                2 => {
                    nums.swap(j, k - 1);
                    k -= 1;
                }
                _ => panic!(),
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sort_colors() {
        let test_cases = vec![
            vec![],
            vec![0],
            vec![1],
            vec![2],
            vec![0, 1],
            vec![0, 2],
            vec![1, 2],
            vec![1, 0],
            vec![2, 0],
            vec![2, 1],
            vec![2, 0, 1],
            vec![2, 0, 2, 1, 1, 0],
            (0..=2).cycle().take(100).collect(),
        ];
        let mut passed = true;
        for nums in test_cases.iter() {
            let mut expected = nums.clone();
            expected.sort();
            let mut actual = nums.clone();
            Solution::sort_colors(&mut actual);
            if expected != actual {
                passed = false;
                eprintln!("nums: {nums:?}, exp: {expected:?}, act: {actual:?}");
            }
        }
        assert!(passed);
    }
}
