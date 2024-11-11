// LeetCode 322. Coin Change.

// use std::cmp::min;
// use std::iter;
pub struct Solution {}

impl Solution {
    pub fn coin_change(coins: Vec<i32>, amount: i32) -> i32 {
        // reserve max value for sentinal for small optimization.
        assert!(amount < i32::MAX - 1);
        if amount <= 0 {
            return 0;
        }
        let sentinal = amount + 1;
        let mut coin_counts: Vec<i32> = vec![sentinal; (amount + 1) as usize];
        coin_counts[0] = 0;
        for i in 1..=amount {
            let mut best_val = sentinal;
            for coin in coins.iter() {
                let prev_i = i - *coin;
                if prev_i >= 0 {
                    let new_val = coin_counts[prev_i as usize] + 1;
                    best_val = std::cmp::min(new_val, best_val);
                }
            }
            coin_counts[i as usize] = std::cmp::min(best_val, coin_counts[i as usize]);
        }
        let last_val = *coin_counts.last().unwrap();
        if last_val >= sentinal {
            return -1;
        }
        return last_val;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_coin_change() {
        assert_eq!(1, Solution::coin_change(vec![1, 5, 10, 25], 25));
        assert_eq!(1, Solution::coin_change(vec![1, 5, 10, 25], 10));
        assert_eq!(3, Solution::coin_change(vec![1, 2, 5], 11));
        assert_eq!(-1, Solution::coin_change(vec![2], 3));
        assert_eq!(0, Solution::coin_change(vec![1], 0));
        assert_eq!(
            834,
            Solution::coin_change(vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], 10_000)
        );
    }
}
