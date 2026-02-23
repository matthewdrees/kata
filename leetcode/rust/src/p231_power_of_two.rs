// LeetCode 231. Power of Two.

struct Solution {}

impl Solution {
    pub fn is_power_of_two(n: i32) -> bool {
        if n <= 0 {
            return false;
        }
        let mut mult = 1;
        loop {
            if mult == n {
                return true;
            }
            if mult >= 1073741824 { // 2^30
                break;
            }
            mult *= 2;
        }
        return false;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_power_of_two() {
        assert_eq!(false, Solution::is_power_of_two(-2));
        assert_eq!(false, Solution::is_power_of_two(0));
        assert_eq!(true, Solution::is_power_of_two(1));
        assert_eq!(true, Solution::is_power_of_two(2));
        assert_eq!(false, Solution::is_power_of_two(3));
        assert_eq!(true, Solution::is_power_of_two(4));
        assert_eq!(false, Solution::is_power_of_two(5));
        assert_eq!(false, Solution::is_power_of_two(6));
        assert_eq!(false, Solution::is_power_of_two(7));
        assert_eq!(true, Solution::is_power_of_two(8));
        assert_eq!(false, Solution::is_power_of_two(9));
        assert_eq!(false, Solution::is_power_of_two(10));
        assert_eq!(false, Solution::is_power_of_two(11));
        assert_eq!(false, Solution::is_power_of_two(12));
        assert_eq!(true, Solution::is_power_of_two(16));
        assert_eq!(false, Solution::is_power_of_two(1073741823));
        assert_eq!(true, Solution::is_power_of_two(1073741824));
        assert_eq!(false, Solution::is_power_of_two(1073741825));
        assert_eq!(false, Solution::is_power_of_two(2147483647));
    }
}
