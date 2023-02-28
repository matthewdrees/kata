// LeetCode 50. Pow(x, n).

struct Solution {}

impl Solution {
    pub fn my_pow(x: f64, n: i32) -> f64 {
        // Exponent by squaring algorithm.
        if n == 0 {
            return 1.0;
        }
        if x == 0.0 {
            return 0.0;
        }
        let mut n: i64 = n as i64;
        let mut x = x;
        if n < 0 {
            n = -n;
            x = 1.0 / x;
        }
        let mut y: f64 = 1.0;
        while n > 1 {
            if n % 2 == 0 {
                x = x * x;
                n = n / 2;
            } else {
                y = x * y;
                x = x * x;
                n = (n - 1) / 2;
            }
        }
        return x * y;
    }
}

fn main() {
    struct TestCase {
        x: f64,
        n: i32,
        exp: f64,
    }

    let test_cases = vec![
        TestCase {
            x: 2.0,
            n: 10,
            exp: 1024.0,
        },
        TestCase {
            x: 2.1,
            n: 3,
            exp: 9.261,
        },
        TestCase {
            x: 2.0,
            n: -2,
            exp: 0.25,
        },
        TestCase {
            x: 0.0,
            n: 0,
            exp: 1.0,
        },
        TestCase {
            x: 2.0,
            n: 0,
            exp: 1.0,
        },
        TestCase {
            x: -2.0,
            n: 0,
            exp: 1.0,
        },
        TestCase {
            x: -2.0,
            n: 1,
            exp: -2.0,
        },
    ];
    for tc in test_cases {
        let act = Solution::my_pow(tc.x, tc.n);
        if tc.exp != act {
            eprintln!(
                "Fail. x: {}, n: {}, exp: {}, act: {}",
                tc.x, tc.n, tc.exp, act
            );
        }
    }
}
