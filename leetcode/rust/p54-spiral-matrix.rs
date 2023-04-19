// LeetCode 54. Spiral Matrix.

use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn spiral_order(matrix: Vec<Vec<i32>>) -> Vec<i32> {
        let mut y_max = matrix.len();
        assert!(y_max >= 1);
        let mut x_max = matrix[0].len();
        assert!(x_max >= 1);
        let mut y_min: usize = 0;
        let mut x_min: usize = 0;

        let mut v: Vec<i32> = Vec::with_capacity(x_max * y_max);
        loop {
            // right
            v.extend_from_slice(&matrix[y_min][x_min..x_max]);
            y_min += 1;
            if y_min >= y_max {
                break;
            }

            // down
            x_max -= 1;
            for y in y_min..y_max {
                v.push(matrix[y][x_max]);
            }
            if x_min >= x_max {
                break;
            }

            // left
            y_max -= 1;
            for x in (x_min..x_max).rev() {
                v.push(matrix[y_max][x]);
            }
            if y_min >= y_max {
                break;
            }

            // up
            for y in (y_min..y_max).rev() {
                v.push(matrix[y][x_min]);
            }
            x_min += 1;
            if x_min >= x_max {
                break;
            }
        }
        return v;
    }
}

fn main() {
    struct TestCase {
        nums: Vec<Vec<i32>>,
        exp: Vec<i32>,
    }
    let test_cases = vec![
        TestCase {
            nums: vec![vec![-100]],
            exp: vec![-100],
        },
        TestCase {
            nums: vec![vec![1, 2], vec![3, 4]],
            exp: vec![1, 2, 4, 3],
        },
        TestCase {
            nums: vec![vec![7, 8]],
            exp: vec![7, 8],
        },
        TestCase {
            nums: vec![vec![1], vec![2]],
            exp: vec![1, 2],
        },
        TestCase {
            nums: vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]],
            exp: vec![1, 2, 3, 6, 9, 8, 7, 4, 5],
        },
        TestCase {
            nums: vec![vec![1, 2, 3, 4], vec![5, 6, 7, 8], vec![9, 10, 11, 12]],
            exp: vec![1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7],
        },
        TestCase {
            nums: vec![
                vec![1, 2, 3, 4],
                vec![5, 6, 7, 8],
                vec![9, 10, 11, 12],
                vec![13, 14, 15, 16],
            ],
            exp: vec![1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10],
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::spiral_order(tc.nums.clone());
        if tc.exp != act {
            eprintln!(
                "FAIL. nums: {:?}, exp: {:?}, act: {:?}",
                tc.nums, tc.exp, act
            );
        }
    }
}
