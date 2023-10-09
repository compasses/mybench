#include "memcpy.h"
#include <cstring>
#include <benchmark/benchmark.h>
void *ptr;

static void BM_ck_memcpy(benchmark::State &state) {
  char* src = new char[state.range(0)];
  char* dst = new char[state.range(0)];
  std::memset(src, 'x', state.range(0));
  std::memset(dst, 'c', state.range(0));
  for (auto _ : state)
    ptr = inline_memcpy(dst, src, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(state.range(0)));
  delete[] src;
  delete[] dst;
}

static void BM_memcpy(benchmark::State &state) {
  char* src = new char[state.range(0)];
  char* dst = new char[state.range(0)];
  std::memset(src, 'x', state.range(0));
  std::memset(dst, 'c', state.range(0));
  for (auto _ : state)
    ptr = std::memcpy(dst, src, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(state.range(0)));
  delete[] src;
  delete[] dst;
}

BENCHMARK(BM_memcpy)->DenseRange(0, 16, 1)->RangeMultiplier(2)->Range(32, 8<<10);
BENCHMARK(BM_ck_memcpy)->DenseRange(0, 16, 1)->RangeMultiplier(2)->Range(32, 8<<10);
BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(128 << 20, 1024 << 20);
BENCHMARK(BM_ck_memcpy)->RangeMultiplier(2)->Range(128 << 20, 1024 << 20);

BENCHMARK_MAIN();
