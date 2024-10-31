use criterion::{black_box, criterion_group, criterion_main, Criterion};

use rust::p198_house_robber;

use rand::{
    distributions::{Distribution, Uniform},
    SeedableRng,
};

fn criterion_benchmark(c: &mut Criterion) {
    let between = Uniform::from(1..400);
    let mut rng = rand::rngs::StdRng::seed_from_u64(42);
    let nums: Vec<i32> = (0..100).map(|_| between.sample(&mut rng)).collect();
    c.bench_function("house robber 100", |b| {
        b.iter(|| p198_house_robber::Solution::rob(black_box(&nums)))
    });
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
