struct Solution {}

impl Solution {
    pub fn generate_matrix(n: i32) -> Vec<Vec<i32>> {
        let matrix_size = n as usize;
        let mut matrix: Vec<Vec<i32>> = vec![vec![0; matrix_size]; matrix_size];
        let mut num = 1;
        let mut dim0: usize = 0;
        let mut dim1: usize = matrix_size;
        loop {
            for x in dim0..dim1 {
                matrix[dim0][x] = num;
                num += 1;
            }
            dim1 -= 1;
            if dim0 == dim1 {
                break;
            }
            for y in dim0 + 1..dim1 {
                matrix[y][dim1] = num;
                num += 1;
            }
            for x in (dim0 + 1..=dim1).rev() {
                matrix[dim1][x] = num;
                num += 1;
            }
            for y in (dim0 + 1..=dim1).rev() {
                matrix[y][dim0] = num;
                num += 1;
            }
            dim0 += 1;
            if dim0 == dim1 {
                break;
            }
        }
        return matrix;
    }
}

fn main() {
    struct TestCase {
        n: i32,
        exp: Vec<Vec<i32>>,
    }
    let test_cases = vec![
        TestCase {
            n: 1,
            exp: vec![vec![1]],
        },
        TestCase {
            n: 2,
            exp: vec![vec![1, 2], vec![4, 3]],
        },
        TestCase {
            n: 3,
            exp: vec![vec![1, 2, 3], vec![8, 9, 4], vec![7, 6, 5]],
        },
        TestCase {
            n: 4,
            exp: vec![
                vec![1, 2, 3, 4],
                vec![12, 13, 14, 5],
                vec![11, 16, 15, 6],
                vec![10, 9, 8, 7],
            ],
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::generate_matrix(tc.n);
        if tc.exp != act {
            println!("Fail, n: {:?}, exp: {:?}, act: {:?}", tc.n, tc.exp, act);
        }
    }
}
