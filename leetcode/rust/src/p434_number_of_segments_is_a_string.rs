// LeetCode 434. Number of Segments in a String.

struct Solution {}

impl Solution {
    pub fn count_segments(s: String) -> i32 {
        let mut seg_num = 0;
        let mut was_space = true;
        for c in s.chars() {
            if c == ' ' {
                was_space = true;
            }
            else if was_space {
                seg_num += 1;
                was_space = false;
            }
        }
        return seg_num;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_count_segments() {
        assert_eq!(0, Solution::count_segments("".to_string()));
        assert_eq!(1, Solution::count_segments("Hello".to_string()));
        assert_eq!(5, Solution::count_segments("Hello, my name is John".to_string()));
        assert_eq!(0, Solution::count_segments("           ".to_string()));
    }
}
