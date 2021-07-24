
#include <benchmark/benchmark.h>

#include <algorithm>

#include "mystl/algorithm.hpp"

const size_t num_elems = 65535;

// Benchmark for ::all_of (above)
static void BM_all_of(benchmark::State &state)
{
  std::vector<int> v(num_elems, 42);
  v[num_elems / 2] = 43;
  for (auto _ : state)
    benchmark::DoNotOptimize(::all_of(v.begin(), v.end(), [](const auto i)
                                      { return i == 42; }));
}
// Register the function as a benchmark
BENCHMARK(BM_all_of);

// Benchmark for std::all_of
static void BM_std_all_of(benchmark::State &state)
{
  std::vector<int> v(num_elems, 42);
  v[num_elems / 2] = 43;
  for (auto _ : state)
    benchmark::DoNotOptimize(std::all_of(v.begin(), v.end(), [](const auto i)
                                         { return i == 42; }));
}
BENCHMARK(BM_std_all_of);

BENCHMARK_MAIN();
