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

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_num_combinations() {
        let mut passed = true;
        struct TC {
            k1: i32,
            k2: i32,
            exp: i32,
        }
        let test_cases = vec![
            TC { k1: 1, k2: 1, exp: 2 },
            TC { k1: 1, k2: 2, exp: 4 },
            TC { k1: 2, k2: 1, exp: 3 },
            TC { k1: 2, k2: 2, exp: 6 },
            TC { k1: 2, k2: 3, exp: 10 },
            TC { k1: 15, k2: 15, exp: 155117520 },
        ];

        for tc in test_cases.iter() {
            let act = num_combinations(tc.k1, tc.k2);
            if tc.exp != act {
                passed = false;
                eprintln!(
                    "(k1: {:?}, k2: {:?}), exp: {:?}, act: {:?}",
                    tc.k1, tc.k2, tc.exp, act
                );
            }
        }
        assert!(passed);
    }

    #[test]
    fn test_count_stairs_1_1() {
        assert_eq!(Solution::climb_stairs(1), 1);
    }
    #[test]
    fn test_count_stairs_2_2() {
        assert_eq!(Solution::climb_stairs(2), 2);
    }
    #[test]
    fn test_count_stairs_3_3() {
        assert_eq!(Solution::climb_stairs(3), 3);
    }
    #[test]
    fn test_count_stairs_4_5() {
        assert_eq!(Solution::climb_stairs(4), 5);
    }
    #[test]
    fn test_count_stairs_5_8() {
        assert_eq!(Solution::climb_stairs(4), 5);
    }
    #[test]
    fn test_count_stairs_6_13() {
        assert_eq!(Solution::climb_stairs(6), 13);
    }
    #[test]
    fn test_count_stairs_7_21() {
        assert_eq!(Solution::climb_stairs(7), 21);
    }
    #[test]
    fn test_count_stairs_8_34() {
        assert_eq!(Solution::climb_stairs(8), 34);
    }
    #[test]
    fn test_count_stairs_45_1836311903() {
        assert_eq!(Solution::climb_stairs(45), 1836311903);
    }
    #[test]
    fn test_count_stairs() {
        let mut passed = true;
        #[derive(Debug)]
        struct TC {
            n: i32,
            exp: i32,
        }

        let test_cases = vec![
            TC { n: 1, exp: 1 },
            TC { n: 2, exp: 3 },
            TC { n: 3, exp: 3 },
            TC { n: 4, exp: 5 },
            TC { n: 5, exp: 8 },
            TC { n: 6, exp: 13 },
            TC { n: 7, exp: 21 },
            TC { n: 8, exp: 34 },
            TC { n: 45, exp: 1836311903 },
        ];

        for tc in test_cases.iter() {
            let act = Solution::climb_stairs(tc.n);
            if tc.exp != act {
                passed = false;
                eprintln!("{tc:?}, act: {act}");
            }
        }
        assert!(passed);
    }
}
