// LeetCode 392. Is Subsequence.

pub struct Solution {}

impl Solution {
    pub fn is_subsequence(s: String, t: String) -> bool {
        let mut sit = s.chars().peekable();
        if sit.peek().is_none() {
            return true;
        }
        for c_t in t.chars() {
            if c_t == *sit.peek().unwrap() {
                sit.next();
                if sit.peek().is_none() {
                    return true;
                }
            }
        }
        false
    }
}

#[cfg(test)]
mod tests {

    #[test]
    fn test_is_subsequence() {
        use crate::solution::Solution;
        assert_eq!(
            true,
            Solution::is_subsequence("abc".to_string(), "ahbgdc".to_string()),
        );
        assert_eq!(
            false,
            Solution::is_subsequence("axc".to_string(), "ahbgdc".to_string()),
        );
    }
}
