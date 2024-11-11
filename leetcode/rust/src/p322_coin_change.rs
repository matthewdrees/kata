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
        struct TC {
            coins: Vec<i32>,
            amount: i32,
            exp: i32,
        }

        let test_cases = vec![
            TC { coins: vec![1, 5, 10, 25], amount: 25, exp: 1 },
            TC { coins: vec![1, 5, 10, 25], amount: 10, exp: 1 },
            TC { coins: vec![1, 2, 5], amount: 11, exp: 3 },
            TC { coins: vec![2], amount: 3, exp: -1 },
            TC { coins: vec![1], amount: 0, exp: 0 },
        ];

        let mut passed = true;
        for tc in test_cases.iter() {
            let act = Solution::coin_change(tc.coins.clone(), tc.amount);
            if tc.exp != act {
                passed = false;
                eprintln!(
                    "(coins: {:?}, amount: {}, exp: {}, act: {}",
                    tc.coins, tc.amount, tc.exp, act
                );
            }
        }
        assert!(passed);
    }
}
