// LeetCode 47. Permutations II.
use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn permute_unique(nums: Vec<i32>) -> Vec<Vec<i32>> {
        if nums.is_empty() {
            return vec![];
        }
        if nums.len() == 1 {
            return vec![nums];
        }
        let mut nums = nums.clone();
        nums.sort_unstable();
        let mut permutations: Vec<Vec<i32>> = Vec::new();
        permutations.push(nums.clone());
        if nums.len() == 2 {
            if nums[0] != nums[1] {
                permutations.push(vec![nums[1], nums[0]]);
            }
            return permutations;
        }
        loop {
            let i1 = nums.len() - 1;
            let i2 = nums.len() - 2;
            if nums[i2] < nums[i1] {
                nums.swap(i1, i2);
                permutations.push(nums.clone());
            }
            let i3 = nums.len() - 3;
            if nums[i3] < nums[i2] {
                let tmp = nums[i1];
                if nums[i3] < nums[i1] {
                    nums[i1] = nums[i2];
                    nums[i2] = nums[i3];
                    nums[i3] = tmp;
                } else {
                    nums[i1] = nums[i3];
                    nums[i3] = nums[i2];
                    nums[i2] = tmp;
                }
                permutations.push(nums.clone());
                continue;
            }

            let mut do_continue = false;
            for i in (0..nums.len() - 3).rev() {
                let n1 = nums[i];
                let n2 = nums[i + 1];
                if n1 < n2 {
                    let mut j = nums.len() - 1;
                    while j >= i + 1 && n1 >= nums[j] {
                        j -= 1;
                    }
                    nums.swap(i, j);
                    let mut k = i + 1;
                    let mut l = nums.len() - 1;
                    while k < l {
                        nums.swap(k, l);
                        k += 1;
                        l -= 1;
                    }
                    permutations.push(nums.clone());
                    do_continue = true;
                    break;
                }
            }
            if do_continue {
                continue;
            }
            break;
        }

        permutations
    }
}

fn main() {
    struct TestCase {
        nums: Vec<i32>,
        exp: Vec<Vec<i32>>,
    }

    let test_cases = vec![
        TestCase {
            nums: vec![1],
            exp: vec![vec![1]],
        },
        TestCase {
            nums: vec![1, 1],
            exp: vec![vec![1, 1]],
        },
        TestCase {
            nums: vec![1, 2],
            exp: vec![vec![1, 2], vec![2, 1]],
        },
        TestCase {
            nums: vec![2, 1],
            exp: vec![vec![1, 2], vec![2, 1]],
        },
        TestCase {
            nums: vec![1, 2, 1],
            exp: vec![vec![1, 1, 2], vec![1, 2, 1], vec![2, 1, 1]],
        },
        TestCase {
            nums: vec![1, 1, 2, 2],
            exp: vec![
                vec![1, 1, 2, 2],
                vec![1, 2, 1, 2],
                vec![1, 2, 2, 1],
                vec![2, 1, 1, 2],
                vec![2, 1, 2, 1],
                vec![2, 2, 1, 1],
            ],
        },
        TestCase {
            nums: vec![1, 2, 3],
            exp: vec![
                vec![1, 2, 3],
                vec![1, 3, 2],
                vec![2, 1, 3],
                vec![2, 3, 1],
                vec![3, 1, 2],
                vec![3, 2, 1],
            ],
        },
        TestCase {
            nums: vec![1, 3, 2, 3],
            exp: vec![
                vec![1, 2, 3, 3],
                vec![1, 3, 2, 3],
                vec![1, 3, 3, 2],
                vec![2, 1, 3, 3],
                vec![2, 3, 1, 3],
                vec![2, 3, 3, 1],
                vec![3, 1, 2, 3],
                vec![3, 1, 3, 2],
                vec![3, 2, 1, 3],
                vec![3, 2, 3, 1],
                vec![3, 3, 1, 2],
                vec![3, 3, 2, 1],
            ],
        },
        TestCase {
            nums: vec![2, 2, 3, 3, 3],
            exp: vec![
                vec![2, 2, 3, 3, 3],
                vec![2, 3, 2, 3, 3],
                vec![2, 3, 3, 2, 3],
                vec![2, 3, 3, 3, 2],
                vec![3, 2, 2, 3, 3],
                vec![3, 2, 3, 2, 3],
                vec![3, 2, 3, 3, 2],
                vec![3, 3, 2, 2, 3],
                vec![3, 3, 2, 3, 2],
                vec![3, 3, 3, 2, 2],
            ],
        },
    ];
    for tc in test_cases {
        let act = Solution::permute_unique(tc.nums.clone());
        if tc.exp != act {
            eprintln!(
                "Fail. nums: {:?}\nexp: {:?}\nact: {:?}",
                tc.nums, tc.exp, act
            );
        }
    }
}
