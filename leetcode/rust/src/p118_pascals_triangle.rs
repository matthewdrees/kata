// LeetCode 118. Pascal's Triangle.

pub struct Solution {}

impl Solution {
    pub fn generate(num_rows: i32) -> Vec<Vec<i32>> {
        let mut v: Vec<Vec<i32>> = Vec::with_capacity(num_rows as usize);
        let mut row: Vec<i32> = Vec::with_capacity(num_rows as usize);
        for _ in 0..num_rows {
            let mut tmp = 1;
            for i in 1..row.len() {
                tmp = tmp + row[i];
                std::mem::swap(&mut tmp, &mut row[i]);
            }
            row.push(1);
            v.push(row.clone());
        }
        return v;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_pascals_triangle() {
        let triangle: Vec<Vec<i32>> = vec![
            vec![1],
            vec![1,1],
            vec![1,2,1],
            vec![1,3,3,1],
            vec![1,4,6,4,1],
            vec![1,5,10,10,5,1],
            vec![1,6,15,20,15,6,1],
        ];
        for i in 0..triangle.len()-1 {
            let triangle_slice = &triangle[0..i];
            assert_eq!(triangle_slice, Solution::generate(i as i32));
        }
    }
}
