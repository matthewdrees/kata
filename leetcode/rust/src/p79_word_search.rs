// LeetCode 79. Word Search

pub struct Solution {}

struct ExistHelper<'a> {
    board: &'a Vec<Vec<char>>,
    word: Vec<char>,
    row_len: usize,
}

impl ExistHelper<'_> {
    fn rec(&self, y: usize, x: usize, board_mask: usize, word_idx: usize) -> bool {
        assert!(word_idx < self.word.len());
        let c = self.word[word_idx];
        if c == self.board[y][x] {
            let mask = 1_usize << (y * self.row_len + x);
            if mask & board_mask != 0 {
                return false;
            }
            if word_idx + 1 == self.word.len() {
                return true;
            }
            if y != 0 {
                if self.rec(y - 1, x, board_mask | mask, word_idx + 1) {
                    return true;
                }
            }
            if x != 0 {
                if self.rec(y, x - 1, board_mask | mask, word_idx + 1) {
                    return true;
                }
            }
            if x + 1 < self.row_len {
                if self.rec(y, x + 1, board_mask | mask, word_idx + 1) {
                    return true;
                }
            }
            if y + 1 < self.board.len() {
                if self.rec(y + 1, x, board_mask | mask, word_idx + 1) {
                    return true;
                }
            }
        }
        return false;
    }
}

impl Solution {
    pub fn exist(board: Vec<Vec<char>>, word: String) -> bool {
        let max_cells = 64_usize; // using usize (64 bits) bitmask for board mask.
        if word.len() > max_cells {
            return false;
        }
        assert!(board.len() >= 1);
        let row_len = board.first().unwrap().len();
        assert!(row_len >= 1);
        assert!(board.len() * row_len < max_cells);
        for row in board.iter() {
            assert!(row_len == (*row).len());
        }
        let eh = ExistHelper { board: &board, word: word.chars().collect(), row_len };
        for y in 0..board.len() {
            for x in 0..row_len {
                let ret = eh.rec(y, x, 0, 0);
                if ret {
                    return true;
                }
            }
        }
        return false;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_exist() {
        assert_eq!(true, Solution::exist(vec![vec!['A']], "A".to_string()));
        assert_eq!(false, Solution::exist(vec![vec!['A']], "B".to_string()));
        assert_eq!(false, Solution::exist(vec![vec!['A']], "AA".to_string()));
        let grid = vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ];
        assert_eq!(true, Solution::exist(grid.clone(), "ABCCED".to_string()));
        assert_eq!(true, Solution::exist(grid.clone(), "SEE".to_string()));
        assert_eq!(false, Solution::exist(grid.clone(), "ABCB".to_string()));
        assert_eq!(false, Solution::exist(grid.clone(), "X".to_string()));
        let grid2 = vec![
            vec!['A', 'S', 'A'],
            vec!['B', 'F', 'D'],
            vec!['C', 'C', 'E'],
            vec!['E', 'S', 'E'],
        ];
        assert_eq!(true, Solution::exist(grid2.clone(), "ABCCED".to_string()));
        assert_eq!(true, Solution::exist(grid2.clone(), "SEE".to_string()));
        assert_eq!(false, Solution::exist(grid2.clone(), "ABCB".to_string()));

        let grid3 = vec![
            vec!['g', 'a', 'b', 'c', 'b', 'a'],
            vec!['a', 'b', 'c', 'b', 'a', 'b'],
            vec!['b', 'c', 'b', 'a', 'b', 'c'],
            vec!['c', 'b', 'a', 'b', 'c', 'b'],
            vec!['b', 'a', 'b', 'c', 'b', 'a'],
            vec!['x', 'b', 'c', 'b', 'a', 'b'],
        ];
        assert_eq!(
            true,
            Solution::exist(
                grid3.clone(),
                "babcbababcbabcbabcbcbabcbabcbagabcbx".to_string()
            )
        );
        assert_eq!(
            true,
            Solution::exist(
                grid3.clone(),
                "abcbababcbabcbabcbcbabcbabcbabxbcbag".to_string()
            )
        );
    }
}
