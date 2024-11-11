use criterion::{black_box, criterion_group, criterion_main, Criterion};

use rust::p322_coin_change;

fn coin_change_benchmark(c: &mut Criterion) {
    let coins = vec![1, 5, 10, 25, 50, 100, 200, 300, 400, 500, 600, 1000];
    c.bench_function("coin changes 10,000, coins = 10", |b| {
        b.iter(|| {
            p322_coin_change::Solution::coin_change(black_box(coins.clone()), black_box(10_000))
        })
    });
}

criterion_group!(benches, coin_change_benchmark);
criterion_main!(benches);
