// LeetCode 202. Happy number.
use std::collections::HashSet;

pub struct Solution {}

fn sum_squares(n: i32) -> i32 {
    let mut total = 0;
    let mut x = n;
    while x != 0 {
        let xmod10 = x % 10;
        total += xmod10 * xmod10;
        x /= 10;
    }
    return total;
}

impl Solution {
    pub fn is_happy(n: i32) -> bool {
        let mut intermediate_solutions = HashSet::new();
        let mut x = n;
        while x != 1 {
            x = sum_squares(x);
            if intermediate_solutions.contains(&x) {
                return false;
            }
            intermediate_solutions.insert(x);
        }
        return true;
    }
}

#[cfg(test)]
mod tests {

    #[test]
    fn test_sum_squares() {
        use crate::solution::sum_squares;
        assert_eq!(1, sum_squares(1));
        assert_eq!(4, sum_squares(2));
        assert_eq!(82, sum_squares(19));
        assert_eq!(100, sum_squares(68));
        assert_eq!(260, sum_squares(2_147_483_647));
    }

    #[test]
    fn test_is_happy() {
        use crate::solution::Solution;
        assert_eq!(true, Solution::is_happy(1));
        assert_eq!(false, Solution::is_happy(2));
        assert_eq!(true, Solution::is_happy(19));
        assert_eq!(false, Solution::is_happy(2_147_483_647));
    }
}
