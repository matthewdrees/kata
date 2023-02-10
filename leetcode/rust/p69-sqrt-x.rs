// LeetCode 69. Sqrt(x).

struct Solution {}

impl Solution {
    pub fn my_sqrt(x: i32) -> i32 {
        if x >= 2147395600 {
            return 46340;
        }
        let x: i64 = x.into();
        let mut ans: i64 = 0;
        let mut base: i64 = 32768; // 2^15
        let mut factor: i64 = 16384; // 2^14
        loop {
            let n = base * base;
            if n == x {
                ans = base;
                break;
            } else if n < x {
                ans = base;
                base += factor;
            } else {
                base -= factor;
            }
            if factor == 0 {
                break;
            }
            factor >>= 1;
        }
        return ans as i32;
    }
}

fn main() {
    struct TestCase {
        x: i32,
        exp: i32,
    }

    let test_cases = vec![
        TestCase { x: 0, exp: 0 },
        TestCase { x: 1, exp: 1 },
        TestCase { x: 2, exp: 1 },
        TestCase { x: 3, exp: 1 },
        TestCase { x: 4, exp: 2 },
        TestCase { x: 5, exp: 2 },
        TestCase { x: 8, exp: 2 },
        TestCase { x: 9, exp: 3 },
        TestCase { x: 10, exp: 3 },
        TestCase { x: 15, exp: 3 },
        TestCase { x: 16, exp: 4 },
        TestCase { x: 24, exp: 4 },
        TestCase { x: 25, exp: 5 },
        TestCase { x: 26, exp: 5 },
        TestCase { x: 35, exp: 5 },
        TestCase { x: 36, exp: 6 },
        TestCase { x: 48, exp: 6 },
        TestCase { x: 49, exp: 7 },
        TestCase { x: 63, exp: 7 },
        TestCase { x: 64, exp: 8 },
        TestCase {
            x: 2147395599,
            exp: 46339,
        },
        TestCase {
            x: 2147395600,
            exp: 46340,
        },
        TestCase {
            x: i32::MAX,
            exp: 46340,
        },
    ];
    for tc in test_cases {
        let act = Solution::my_sqrt(tc.x);
        if tc.exp != act {
            eprintln!("Fail. x: {}, exp: {}, act: {}", tc.x, tc.exp, act);
        }
    }
}
