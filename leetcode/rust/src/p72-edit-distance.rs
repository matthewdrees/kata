// LeetCode 72. Edit Distance.

use std::cmp;
use std::vec::Vec;

pub struct SolutionTopDown {}

fn min_distance_recur(
    matrix: &mut Vec<Vec<Option<usize>>>,
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
    match matrix[vc1_index][vc2_index] {
        Some(cached_val) => {
            return cached_val;
        }
        None => {}
    }
    if vc1[vc1_index - 1] == vc2[vc2_index - 1] {
        return min_distance_recur(matrix, vc1, vc2, vc1_index - 1, vc2_index - 1);
    } else {
        let insert_operation = min_distance_recur(matrix, vc1, vc2, vc1_index, vc2_index - 1);
        let delete_operation = min_distance_recur(matrix, vc1, vc2, vc1_index - 1, vc2_index);
        let replace_operation = min_distance_recur(matrix, vc1, vc2, vc1_index - 1, vc2_index - 1);

        let min_edit_distance = cmp::min(
            insert_operation,
            cmp::min(delete_operation, replace_operation),
        ) + 1;
        matrix[vc1_index][vc2_index] = Some(min_edit_distance);
        return min_edit_distance;
    }
}

impl SolutionTopDown {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let vc1 = word1.chars().collect();
        let vc2 = word2.chars().collect();
        let mut matrix: Vec<Vec<Option<usize>>> =
            vec![vec![None; word2.len() + 1]; word1.len() + 1];
        return min_distance_recur(&mut matrix, &vc1, &vc2, vc1.len(), vc2.len()) as i32;
    }
}


pub struct Solution {}

impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        if word1.len() == 0 {
            return word2.len();
        }
        if word2.len() == 0 {
            return word1.len();
        }

        let mut dp: Vec<Vec<usize>>
    }
}
#[cfg(test)]
mod tests {

    #[test]
    fn test_top_down_min_distance() {
        use crate::solution::SolutionTopDown;
        assert_eq!(
            0,
            SolutionTopDown::min_distance("".to_string(), "".to_string())
        );
        assert_eq!(
            3,
            SolutionTopDown::min_distance("".to_string(), "grr".to_string())
        );
        assert_eq!(
            10,
            SolutionTopDown::min_distance("immastring".to_string(), "".to_string())
        );
        assert_eq!(
            3,
            SolutionTopDown::min_distance("horse".to_string(), "ros".to_string())
        );
        assert_eq!(
            5,
            SolutionTopDown::min_distance("intention".to_string(), "execution".to_string())
        );
        assert_eq!(
            1,
            SolutionTopDown::min_distance("aba".to_string(), "abc".to_string())
        );
        assert_eq!(479, SolutionTopDown::min_distance("jOkCLDXymxCHTCru1QzsD6PZ5QR7PouRwLyT0wQiy5ojFDmb4uNV43EEDKlJXbnhoDdPWv22gpVjQkz86Oik4dyjThGdM0i2ZhCJUAp1ERyoWmP6gLZGxeogsFqVqUGx9mnZfX1wRgsPMoTPOX2u5rxekdlWVAx2skPE9xbFzlcvoV0BxAW3xXiKbIVsiHSlWemKGhkKNZSOMqoESMXlOfhDmJBFYC0unZR7617qYVS9R74bREJG0u1A5tGFgTKHKJmj004vlXe2eNgf1Pqkaweo9OPhuWknaes3q8ub9iqARwqd0uFLdm1I0ZHk5le3ZA8s670pwEJPpGAhal67LxTXItnIhrVR60OPXWc1A0MRIC7FvUQ9oaEa8fJvE0f7DNbgVibeBE8xVH1tlhUqbXDpsku60tCCZDlCoJ3KRvSmRSuZAzpNC7lC07ogm3Do1XqF563IkS7nqQqNBqYdW3lR55XbDNG1VgPg3GjlsfrEF8qpI9f2".to_string(), "3bnGMpetyJ9SJKxtZGl2e9Ur9JrDIrcfbkqZ2WDKuOL9Ay0gC49rMO2DaSmR190HXAYkwa6j2OndsaJyHKDyXn6ugwInnlFs5uvhBGovJLD8pVXFfed9yPP3zOkQec1qHBmlejkC8svWnjjepCKsYCYix7L4LEaL5yycNtSuuAtZUwajybDCk5od0UdtJX6R1ErE3lUUOYNXp8Sqq5cwnPuGzSXwEeihSDKSpPK0z6xCF2BJwun3F0HXLZdlLgDAjqDJso71CO5kLpdZnIVLwbKkHHfBSCRxC2iNwrH5tMmhFsTKVaBdnnSisbXYMXqr68RBISBGsjucylAHScIrUPKvZj6Figk1IAr6XtxAv4qkhvXxz2Mk47fX9dq4H8N6UwqAtzwxvB3gm45DOLQfykIzQEr69hsK9RQq7z6vD2kkoUzFBf339VojZW4xQmheU1PrQcWIR4a4PKzsauwbP69aS0ah2VSAFL9vL4yjQG5Loq2Rda21".to_string()));
    }

    fn test_min_distance() {
        use crate::solution::Solution;
        assert_eq!(
            0,
            Solution::min_distance("".to_string(), "".to_string())
        );
        assert_eq!(
            3,
            Solution::min_distance("".to_string(), "grr".to_string())
        );
        assert_eq!(
            10,
            Solution::min_distance("immastring".to_string(), "".to_string())
        );
        assert_eq!(
            3,
            Solution::min_distance("horse".to_string(), "ros".to_string())
        );
        assert_eq!(
            5,
            Solution::min_distance("intention".to_string(), "execution".to_string())
        );
        assert_eq!(
            1,
            Solution::min_distance("aba".to_string(), "abc".to_string())
        );
        assert_eq!(479, Solution::min_distance("jOkCLDXymxCHTCru1QzsD6PZ5QR7PouRwLyT0wQiy5ojFDmb4uNV43EEDKlJXbnhoDdPWv22gpVjQkz86Oik4dyjThGdM0i2ZhCJUAp1ERyoWmP6gLZGxeogsFqVqUGx9mnZfX1wRgsPMoTPOX2u5rxekdlWVAx2skPE9xbFzlcvoV0BxAW3xXiKbIVsiHSlWemKGhkKNZSOMqoESMXlOfhDmJBFYC0unZR7617qYVS9R74bREJG0u1A5tGFgTKHKJmj004vlXe2eNgf1Pqkaweo9OPhuWknaes3q8ub9iqARwqd0uFLdm1I0ZHk5le3ZA8s670pwEJPpGAhal67LxTXItnIhrVR60OPXWc1A0MRIC7FvUQ9oaEa8fJvE0f7DNbgVibeBE8xVH1tlhUqbXDpsku60tCCZDlCoJ3KRvSmRSuZAzpNC7lC07ogm3Do1XqF563IkS7nqQqNBqYdW3lR55XbDNG1VgPg3GjlsfrEF8qpI9f2".to_string(), "3bnGMpetyJ9SJKxtZGl2e9Ur9JrDIrcfbkqZ2WDKuOL9Ay0gC49rMO2DaSmR190HXAYkwa6j2OndsaJyHKDyXn6ugwInnlFs5uvhBGovJLD8pVXFfed9yPP3zOkQec1qHBmlejkC8svWnjjepCKsYCYix7L4LEaL5yycNtSuuAtZUwajybDCk5od0UdtJX6R1ErE3lUUOYNXp8Sqq5cwnPuGzSXwEeihSDKSpPK0z6xCF2BJwun3F0HXLZdlLgDAjqDJso71CO5kLpdZnIVLwbKkHHfBSCRxC2iNwrH5tMmhFsTKVaBdnnSisbXYMXqr68RBISBGsjucylAHScIrUPKvZj6Figk1IAr6XtxAv4qkhvXxz2Mk47fX9dq4H8N6UwqAtzwxvB3gm45DOLQfykIzQEr69hsK9RQq7z6vD2kkoUzFBf339VojZW4xQmheU1PrQcWIR4a4PKzsauwbP69aS0ah2VSAFL9vL4yjQG5Loq2Rda21".to_string()));
    }

}
