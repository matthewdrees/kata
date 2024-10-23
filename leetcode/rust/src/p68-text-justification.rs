// LeetCode 68. Text Justification.
use std::vec::Vec;

struct Solution {}

fn left_justify(v: &[String], width: usize) -> String {
    return format!("{:<1$}", v.join(" "), width);
}

fn left_right_justify(v: &[String], width: usize, line_len: usize) -> String {
    assert!(v.len() >= 2);

    let total_spaces = (width + v.len()) - line_len;
    let min_spaces_between_words = total_spaces / (v.len() - 1);
    let num_extra_spaces = total_spaces % (v.len() - 1);
    let mut spaces = " ".repeat(min_spaces_between_words + 1);
    let mut line = String::with_capacity(width);
    for (i, s) in v.iter().enumerate() {
        line.push_str(s);
        if i + 1 == v.len() {
            break;
        }
        if i == num_extra_spaces {
            spaces.pop();
        }
        line.push_str(&spaces);
    }
    return line;
}

impl Solution {
    pub fn full_justify(words: Vec<String>, max_width: i32) -> Vec<String> {
        assert!(words.len() >= 1);
        let max_width = max_width as usize;
        let mut l: usize = 0;
        let mut lines: Vec<String> = Vec::new();
        let mut line_len: usize = 0;
        for (r, word) in words.iter().enumerate() {
            let word_len = word.len();
            if line_len + word_len > max_width {
                let is_more_than_one_word = r - l > 1;
                if is_more_than_one_word {
                    lines.push(left_right_justify(&words[l..r], max_width, line_len));
                } else {
                    lines.push(left_justify(&words[l..r], max_width));
                }
                l = r;
                line_len = 0;
            }
            line_len += word_len + 1;
        }
        if l != words.len() {
            lines.push(left_justify(&words[l..], max_width));
        }
        return lines;
    }
}

fn test_left_justify() {
    struct TestCase {
        words: String,
        width: usize,
        exp: String,
    }

    let test_cases = vec![TestCase {
        words: "a".to_string(),
        width: 5,
        exp: "a    ".to_string(),
    }];

    for tc in test_cases.iter() {
        let words: Vec<String> = tc.words.split(" ").map(str::to_string).collect();
        let act = left_justify(&words[..], tc.width);
        if tc.exp != act {
            println!(
                "Fail, words: {:?}, width: {}, exp: {:?}, act: {:?}",
                tc.words, tc.width, tc.exp, act
            );
        }
    }
}

fn test_left_right_justify() {
    struct TestCase {
        words: String,
        width: usize,
        line_len: usize,
        exp: String,
    }

    let test_cases = vec![
        TestCase {
            words: "a b".to_string(),
            width: 3,
            line_len: 4,
            exp: "a b".to_string(),
        },
        TestCase {
            words: "a b".to_string(),
            width: 4,
            line_len: 4,
            exp: "a  b".to_string(),
        },
        TestCase {
            words: "a b c".to_string(),
            width: 5,
            line_len: 6,
            exp: "a b c".to_string(),
        },
        TestCase {
            words: "a b c".to_string(),
            width: 6,
            line_len: 6,
            exp: "a  b c".to_string(),
        },
        TestCase {
            words: "a b c".to_string(),
            width: 7,
            line_len: 6,
            exp: "a  b  c".to_string(),
        },
    ];

    for tc in test_cases.iter() {
        let words: Vec<String> = tc.words.split(" ").map(str::to_string).collect();
        let act = left_right_justify(&words[..], tc.width, tc.line_len);
        if tc.exp != act {
            println!(
                "Fail, words: {:?}, width: {}, line_len: {}, exp: {:?}, act: {:?}",
                tc.words, tc.width, tc.line_len, tc.exp, act
            );
        }
    }
}

fn test_full_justify() {
    struct TestCase {
        words: String,
        max_width: i32,
        exp: Vec<String>,
    }

    let test_cases = vec![
        TestCase {
            words: "Imma be".to_string(),
            max_width: 7,
            exp: vec!["Imma be".to_string()],
        },
        TestCase {
            words: "Imma be".to_string(),
            max_width: 8,
            exp: vec!["Imma be ".to_string()],
        },
        TestCase {
            words: "Imma be real".to_string(),
            max_width: 6,
            exp: vec![
                "Imma  ".to_string(),
                "be    ".to_string(),
                "real  ".to_string(),
            ],
        },
        TestCase {
            words: "Imma be real".to_string(),
            max_width: 7,
            exp: vec!["Imma be".to_string(), "real   ".to_string()],
        },
        TestCase {
            words: "Imma be real".to_string(),
            max_width: 8,
            exp: vec!["Imma  be".to_string(), "real    ".to_string()],
        },
    ];
    for tc in test_cases.iter() {
        let words = tc.words.split(" ").map(str::to_string).collect();
        let act = Solution::full_justify(words, tc.max_width);
        if tc.exp != act {
            println!(
                "Fail. words: {:?}, max_width: {}, exp: {:?}, act: {:?}",
                tc.words, tc.max_width, tc.exp, act
            );
        }
    }
}

fn main() {
    test_left_justify();
    test_left_right_justify();
    test_full_justify();
}
