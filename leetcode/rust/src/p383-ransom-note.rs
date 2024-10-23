// LeetCode 383. Ransom Note.
use std::collections::HashMap;

pub struct Solution {}

impl Solution {
    pub fn can_construct(ransom_note: String, magazine: String) -> bool {
        let mut counts: HashMap<char, i32> = HashMap::new();
        for c in magazine.chars() {
            counts
                .entry(c)
                .and_modify(|counter| *counter += 1)
                .or_insert(1);
        }
        for c in ransom_note.chars() {
            match counts.get_mut(&c) {
                Some(count) => {
                    if *count <= 0 {
                        return false;
                    }
                    *count -= 1;
                }
                None => {
                    return false;
                }
            }
        }
        return true;
    }
}

#[cfg(test)]
mod tests {

    #[test]
    fn test_can_construct() {
        use crate::solution::Solution;
        assert_eq!(
            false,
            Solution::can_construct("a".to_string(), "b".to_string()),
        );
        assert_eq!(
            false,
            Solution::can_construct("aa".to_string(), "ab".to_string()),
        );
        assert_eq!(
            true,
            Solution::can_construct("aa".to_string(), "aab".to_string()),
        );
    }
}
