#include "benchmark/benchmark.h"
#include "jemalloc/jemalloc.h"

static size_t kBatchSize = 10000;

static void alloc_mem_n(size_t size) {
    std::vector<char*> kVec(kBatchSize, 0);
    for (int i = 0; i < kBatchSize; ++i) {
        auto p = new char[size];
        p[0] = i;
        benchmark::ClobberMemory();
        kVec[i] = p;
    }
    for (auto &p : kVec) {
        delete p;
        p = nullptr;
    }
}

static void BM_SomeFunction(benchmark::State& state) {
    for (auto _ : state) {
        alloc_mem_n(state.range(0));
    }
}


BENCHMARK(BM_SomeFunction)
    ->Unit(benchmark::kMillisecond)
    ->Iterations(100)
    ->Threads(24)
    ->DenseRange(1792, 2048, 64)
    ->DenseRange(2048, 2560, 128)
    ->DenseRange(2560, 3072, 128)
    ->DenseRange(3072, 3584, 128)
    ->DenseRange(3584, 4096, 128)
    ->DenseRange(4096, 5120, 256)
    ->DenseRange(5120, 6144, 256);

BENCHMARK_MAIN();