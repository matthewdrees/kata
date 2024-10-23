// LeetCode 70. Climbing Stairs.

use std::cmp;

struct Solution {}

// Calculate the number of combinations with varying number of k elements.
fn num_combinations(k1: i32, k2: i32) -> i32 {
    if k1 == 0 || k2 == 0 {
        return 1;
    }
    let min_k = cmp::min(k1, k2) as i64;
    let max_k = cmp::max(k1, k2) as i64;
    let mut tot: i64 = 1;
    for i in 1..=min_k {
        tot *= i + max_k;
        tot /= i;
    }

    return tot as i32;
}

impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        assert!(n >= 1 && n <= 45);
        let mut tot = 1; // for all ones.
        for num2s in 1..=n / 2 {
            let num1s = n - num2s * 2;
            tot += num_combinations(num1s, num2s);
        }
        return tot;
    }
}

fn test_num_combinations() {
    struct TestCase {
        k1: i32,
        k2: i32,
        exp: i32,
    }
    let test_cases = vec![
        TestCase {
            k1: 1,
            k2: 1,
            exp: 2,
        },
        TestCase {
            k1: 1,
            k2: 2,
            exp: 3,
        },
        TestCase {
            k1: 2,
            k2: 1,
            exp: 3,
        },
        TestCase {
            k1: 2,
            k2: 2,
            exp: 6,
        },
        TestCase {
            k1: 2,
            k2: 3,
            exp: 10,
        },
        TestCase {
            k1: 15,
            k2: 15,
            exp: 155117520,
        },
    ];

    for tc in test_cases.iter() {
        let act = num_combinations(tc.k1, tc.k2);
        if tc.exp != act {
            eprint!(
                "test_num_combinations Fail, k1: {:?}, k2: {:?}, exp: {:?}, act: {:?}\n",
                tc.k1, tc.k2, tc.exp, act
            );
        }
    }
}

fn test_count_stairs() {
    struct TestCase {
        n: i32,
        exp: i32,
    }

    let test_cases = vec![
        TestCase { n: 1, exp: 1 },
        TestCase { n: 2, exp: 2 },
        TestCase { n: 3, exp: 3 },
        TestCase { n: 4, exp: 5 },
        TestCase { n: 5, exp: 8 },
        TestCase { n: 6, exp: 13 },
        TestCase { n: 7, exp: 21 },
        TestCase { n: 8, exp: 34 },
        TestCase {
            n: 45,
            exp: 1836311903,
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::climb_stairs(tc.n);
        if tc.exp != act {
            eprintln!(
                "test_climb_stairs Fail, n: {:?}, exp: {:?}, act: {:?}\n",
                tc.n, tc.exp, act
            );
        }
    }
}

fn main() {
    test_num_combinations();
    test_count_stairs();
}
