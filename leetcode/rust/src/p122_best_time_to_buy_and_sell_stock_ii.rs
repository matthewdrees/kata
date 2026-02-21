// LeetCode 122. Best Time to Buy and Sell Stock II

struct Solution {}

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut profit = 0;
        for window in prices.windows(2) {
            if let [p1, p2] = window {
                if p1 <= p2 {
                    profit += p2 - p1;
                }
            }
        }
        return profit;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_profit() {
        assert_eq!(0, Solution::max_profit(vec![]));
        assert_eq!(7, Solution::max_profit(vec![7,1,5,3,6,4]));
        assert_eq!(4, Solution::max_profit(vec![1,2,3,4,5]));
        assert_eq!(0, Solution::max_profit(vec![7,6,4,3,1]));
    }
}