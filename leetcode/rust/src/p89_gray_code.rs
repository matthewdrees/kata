// LeetCode 89. Gray Code.

pub struct Solution {}

impl Solution {
    pub fn gray_code(n: i32) -> Vec<i32> {
        assert!(n >= 1 && n <= 16);
        if n == 1 {
            return vec![0, 1];
        }
        let mut v = Solution::gray_code(n - 1);
        let mut v2 = v.clone();
        v2.reverse();
        v2.iter_mut()
            .for_each(|x| *x += i32::pow(2, (n - 1) as u32));
        v.append(&mut v2);
        return v;
    }
}

#[cfg(test)]
fn is_off_by_one_bit(a: i32, b: i32) -> bool {
    return (a ^ b).count_ones() == 1;
}
#[cfg(test)]
fn is_valid_gray_code(code: &Vec<i32>) -> bool {
    assert!(code.len() >= 2);
    let mut code2 = code.clone();
    code2.sort();
    if !code2.iter().cloned().eq(0..code2.len() as i32) {
        eprintln!("gray code doesn't have unique numbers: {code:?}");
        return false;
    }

    if (code[0] ^ *code.last().unwrap()).count_ones() != 1 {
        return false;
    }
    for w in code.windows(2) {
        if (w[0] ^ w[1]).count_ones() != 1 {
            return false;
        }
    }
    return true;
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_gray_code() {
        for n in 1..=16 {
            let code = Solution::gray_code(n);
            assert!(
                is_valid_gray_code(&code),
                "bad code, n: {n}, code: {code:?}"
            );
        }
    }

    #[test]
    fn test_is_off_by_one_bit() {
        assert!(is_off_by_one_bit(0, 1));
        assert!(is_off_by_one_bit(1, 0));
        assert!(is_off_by_one_bit(1, 3));
        assert!(is_off_by_one_bit(7, 5));
        assert!(is_off_by_one_bit(5, 4));
        assert!(is_off_by_one_bit(4, 6));
        assert!(is_off_by_one_bit(6, 2));

        assert!(!is_off_by_one_bit(0, 0));
        assert!(!is_off_by_one_bit(0, 3));
        assert!(!is_off_by_one_bit(7, 0));
    }
}
