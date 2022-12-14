// LeetCode 48. Rotate Image.

use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn rotate(matrix: &mut Vec<Vec<i32>>) {
        let mut lo: usize = 0;
        let mut hi: usize = matrix.len() - 1;
        while lo < hi {
            for i in 0..hi - lo {
                let tmp = matrix[lo][lo + i];
                matrix[lo][lo + i] = matrix[hi - i][lo];
                matrix[hi - i][lo] = matrix[hi][hi - i];
                matrix[hi][hi - i] = matrix[lo + i][hi];
                matrix[lo + i][hi] = tmp;
            }
            lo += 1;
            hi -= 1;
        }
    }
}

fn main() {
    struct TestCase {
        matrix: Vec<Vec<i32>>,
        exp: Vec<Vec<i32>>,
    }

    let test_cases = vec![
        TestCase {
            matrix: vec![vec![5]],
            exp: vec![vec![5]],
        },
        TestCase {
            matrix: vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]],
            exp: vec![vec![7, 4, 1], vec![8, 5, 2], vec![9, 6, 3]],
        },
        TestCase {
            matrix: vec![
                vec![5, 1, 9, 11],
                vec![2, 4, 8, 10],
                vec![13, 3, 6, 7],
                vec![15, 14, 12, 16],
            ],
            exp: vec![
                vec![15, 13, 2, 5],
                vec![14, 3, 4, 1],
                vec![12, 6, 8, 9],
                vec![16, 7, 10, 11],
            ],
        },
        TestCase {
            matrix: vec![
                vec![1, 2, 3, 4, 5],
                vec![6, 7, 8, 9, 10],
                vec![11, 12, 13, 14, 15],
                vec![16, 17, 18, 19, 20],
                vec![21, 22, 23, 24, 25],
            ],
            exp: vec![
                vec![21, 16, 11, 6, 1],
                vec![22, 17, 12, 7, 2],
                vec![23, 18, 13, 8, 3],
                vec![24, 19, 14, 9, 4],
                vec![25, 20, 15, 10, 5],
            ],
        },
    ];

    for tc in test_cases.iter() {
        let mut act = tc.matrix.clone();
        Solution::rotate(&mut act);
        if tc.exp != act {
            println!(
                "FAIL. matrix: {:?}, exp: {:?}, act: {:?}",
                tc.matrix, tc.exp, act
            );
        }
    }
}
