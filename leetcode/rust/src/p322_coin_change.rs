// LeetCode 322. Coin Change.

pub struct Solution {}

impl Solution {
    pub fn coin_change(coins: Vec<i32>, amount: i32) -> i32 {
        assert!(0 <= amount && amount <= 1_000);
        let mut vals: Vec<i32> = vec![-1; (amount + 1) as usize];
        vals[0] = 0;
        for i in 1..=amount {
            for coin in coins.iter() {
                let prev_i = i - *coin;
                if prev_i < 0 {
                    continue;
                }
                let new_val = vals[prev_i as usize] + 1;
                if new_val == 0 {
                    continue;
                }
                let cur_val = vals[i as usize];
                if cur_val == -1 || new_val < cur_val {
                    vals[i as usize] = new_val;
                }
            }
        }
        return *vals.last().unwrap();
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
