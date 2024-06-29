#include <benchmark/benchmark.h>
#include <iostream>

inline unsigned long intHash64(unsigned long x)
{
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;

    return x;
}

template <typename T>
inline size_t DefaultHash64(std::enable_if_t<(sizeof(T) <= sizeof(unsigned long)), T> key)
{
    union
    {
        T in;
        unsigned long out;
    } u;
    u.out = 0;
    u.in = key;
    return intHash64(u.out);
}


typedef unsigned __int128 uint128_t;
inline uint64_t umul128(uint64_t a, uint64_t b, uint64_t* high) {
    auto result = static_cast<uint128_t>(a) * static_cast<uint128_t>(b);
    *high = static_cast<uint64_t>(result >> 64u);
    return static_cast<uint64_t>(result);
}

template <int n>
struct phmap_mix {
    inline size_t operator()(size_t) const;
};

template <>
class phmap_mix<4> {
public:
    inline size_t operator()(size_t a) const {
        static constexpr uint64_t kmul = 0xcc9e2d51UL;
        uint64_t l = a * kmul;
        return static_cast<size_t>(l ^ (l >> 32u));
    }
};

template <>
class phmap_mix<8> {
public:
    // Very fast mixing (similar to Abseil)
    inline size_t operator()(size_t a) const {
        static constexpr uint64_t k = 0xde5fb9d2630458e9ULL;
        uint64_t h;
        uint64_t l = umul128(a, k, &h);
        return static_cast<size_t>(h + l);
    }
};


static void BM_ck_default_hash(benchmark::State &state) {
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(0); ++i)
            benchmark::DoNotOptimize(DefaultHash64<size_t>(i));
    }
    
      state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(state.range(0)));
}

static void BM_phmap_mix_hash(benchmark::State &state) {
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(0); ++i)
            benchmark::DoNotOptimize(phmap_mix<sizeof(size_t)>()(std::hash<size_t>()(i)));
    }
    
      state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(state.range(0)));
}




// BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(128 << 20, 1024 << 20);
BENCHMARK(BM_ck_default_hash)->RangeMultiplier(10)->Range(1000000, 100000000);
BENCHMARK(BM_phmap_mix_hash)->RangeMultiplier(10)->Range(1000000, 100000000);


BENCHMARK_MAIN();
