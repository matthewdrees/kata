// LeetCode 125. Valid Palindrome.

struct Solution {}

impl Solution {
    pub fn is_palindrome(s: String) -> bool {
        let alphanumeric_string : String = s.chars().filter(|c| c.is_alphanumeric()).collect();
        let lowercase_string = alphanumeric_string.to_lowercase();
        return lowercase_string.chars().eq(lowercase_string.chars().rev());
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_palindrome() {
        assert_eq!(true, Solution::is_palindrome("a".to_string()));
        assert_eq!(true, Solution::is_palindrome(" a".to_string()));
        assert_eq!(true, Solution::is_palindrome("a ".to_string()));
        assert_eq!(false, Solution::is_palindrome("ab".to_string()));
        assert_eq!(false, Solution::is_palindrome("a1".to_string()));
        assert_eq!(true, Solution::is_palindrome("aba".to_string()));
        assert_eq!(false, Solution::is_palindrome("abc".to_string()));
        assert_eq!(true, Solution::is_palindrome("A man, a plan, a canal: Panama".to_string()));
    }
}
