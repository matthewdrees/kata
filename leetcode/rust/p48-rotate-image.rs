// LeetCode 48. Rotate Image.

use std::vec::Vec;

struct Solution {}

impl Solution {
    pub fn rotate(matrix: &mut Vec<Vec<i32>>) {
        let mut usize lo = 0;
        let mut usize hi = matrix.len() - 1;
        while (lo < hi) {
            for i : usize in 0 .. (hi - lo) { 
                let &mut p1 = matrix[lo][lo+i];
                let &mut p2 = matrix[hi - i][lo];
                let &mut p3 = matrix[hi][hi - i];
                let &mut p3 = matrix[lo + i][hi];
                let tmp = p1;
                p1 = p2;
                p2 = p3;
                p3 = p4;
                p4 = tmp;
            }
            lo += 1;
            hi += 1;
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
            nums: vec![vec![5]],
            exp: vec![vec![5]],
        },
    ];

    for tc in test_cases.iter() {
        let mut act = tc.matrix.clone();
        Solution::rotate(act);
        if tc.exp != act {
            println!("FAIL. matrix: {:?}, exp: {:?}, act: {:?}", tc.matrix, tc.exp, act);
        }
    }
}
