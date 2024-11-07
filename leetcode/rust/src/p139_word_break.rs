// LeetCode 139. Word Break.

pub struct Solution {}

struct WordBreakHelper<'a> {
    word_dict: &'a Vec<String>,
    visited: Vec<Option<bool>>,
}

impl WordBreakHelper<'_> {
    fn rec(&mut self, sp: &str) -> bool {
        let visited_sp_idx = self.visited.len() - sp.len();
        if let Some(visit) = self.visited[visited_sp_idx] {
            return visit;
        }
        for word in self.word_dict.iter() {
            let word_str = word.as_str();
            if sp.starts_with(word_str) {
                let new_s_str = &sp[word_str.len()..];
                if new_s_str.is_empty() || self.rec(new_s_str) {
                    self.visited[visited_sp_idx] = Some(true);
                    return true;
                }
            }
        }
        self.visited[visited_sp_idx] = Some(false);
        return false;
    }
}

impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let mut wbh = WordBreakHelper { word_dict: &word_dict, visited: vec![None; s.len()] };
        return wbh.rec(&s);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_word_break() {
        let mut passed = true;
        struct TC {
            s: String,
            word_dict: Vec<String>,
            exp: bool,
        }
        let test_cases = vec![
            TC {
                s: "leetcode".to_string(),
                word_dict: vec!["leet".to_string(), "code".to_string()],
                exp: true,
            },
            TC {
                s: "applepenapple".to_string(),
                word_dict: vec!["apple".to_string(), "pen".to_string()],
                exp: true,
            },
            TC {
                s: "catsandog".to_string(),
                word_dict: vec![
                    "cats".to_string(),
                    "dog".to_string(),
                    "sand".to_string(),
                    "and".to_string(),
                    "cat".to_string(),
                ],
                exp: false,
            },
            TC {
                s: "catskicatcats".to_string(),
                word_dict: vec![
                    "cats".to_string(),
                    "cat".to_string(),
                    "dog".to_string(),
                    "ski".to_string(),
                ],
                exp: true,
            },
            TC {
                s: "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab".to_string(),
                word_dict: vec![
                    "a".to_string(),
                    "aa".to_string(),
                    "aaa".to_string(),
                    "aaaa".to_string(),
                    "aaaaa".to_string(),
                    "aaaaaa".to_string(),
                    "aaaaaaa".to_string(),
                    "aaaaaaaa".to_string(),
                    "aaaaaaaaa".to_string(),
                    "aaaaaaaaaa".to_string(),
                ],
                exp: false,
            }
        ];

        for tc in test_cases.iter() {
            let act = Solution::word_break(tc.s.clone(), tc.word_dict.clone());
            if tc.exp != act {
                passed = false;
                eprintln!(
                    "(s: {:?}, word_dict: {:?}), exp: {}, act: {}",
                    tc.s, tc.word_dict, tc.exp, act
                );
            }
        }
        assert!(passed);
    }
}
