// LeetCode 72. Edit Distance.

use std::cmp;
use std::vec::Vec;

struct Solution {}

fn min_distance_recur(
    vc1: &Vec<char>,
    vc2: &Vec<char>,
    vc1_index: usize,
    vc2_index: usize,
) -> usize {
    if vc1_index == 0 {
        return vc2_index;
    }
    if vc2_index == 0 {
        return vc1_index;
    }
    if vc1[vc1_index - 1] == vc2[vc2_index - 1] {
        return min_distance_recur(vc1, vc2, vc1_index - 1, vc2_index - 1);
    } else {
        let insert_operation = min_distance_recur(vc1, vc2, vc1_index, vc2_index - 1);
        let delete_operation = min_distance_recur(vc1, vc2, vc1_index - 1, vc2_index);
        let replace_operation = min_distance_recur(vc1, vc2, vc1_index - 1, vc2_index - 1);

        return cmp::min(
            insert_operation,
            cmp::min(delete_operation, replace_operation),
        ) + 1;
    }
}

impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let vc1 = word1.chars().collect();
        let vc2 = word2.chars().collect();
        return min_distance_recur(&vc1, &vc2, vc1.len(), vc2.len()) as i32;
    }
}

fn test_min_distance() {
    struct TestCase {
        word1: String,
        word2: String,
        exp: i32,
    }
    let test_cases = vec![
        TestCase {
            word1: "".to_string(),
            word2: "".to_string(),
            exp: 0,
        },
        TestCase {
            word1: "".to_string(),
            word2: "grr".to_string(),
            exp: 3,
        },
        TestCase {
            word1: "immastring".to_string(),
            word2: "".to_string(),
            exp: 10,
        },
        TestCase {
            word1: "horse".to_string(),
            word2: "ros".to_string(),
            exp: 3,
        },
        TestCase {
            word1: "intention".to_string(),
            word2: "execution".to_string(),
            exp: 5,
        },
        TestCase {
            word1: "aba".to_string(),
            word2: "abc".to_string(),
            exp: 1,
        },
    ];

    for tc in test_cases.iter() {
        let act = Solution::min_distance(tc.word1.clone(), tc.word2.clone());
        if tc.exp != act {
            eprint!(
                "Fail, k1: {:?}, k2: {:?}, exp: {:?}, act: {:?}\n",
                tc.word1, tc.word2, tc.exp, act
            );
        }
    }
}

fn main() {
    test_min_distance();
}
