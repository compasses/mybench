#include <iostream>
#include <chrono>

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

size_t h;
size_t s;

void test_ck()
{
    const auto start{std::chrono::steady_clock::now()};
    for (int i = 0; i < 100000000; ++i)
    {
        h = DefaultHash64<size_t>(i);
        __asm__ __volatile__("");
    }
    s = h;
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << elapsed_seconds.count() << "s\n";
}

void test_phmap()
{
    const auto start{std::chrono::steady_clock::now()};
    for (int i = 0; i < 100000000; ++i)
    {
        h = phmap_mix<sizeof(size_t)>()(std::hash<size_t>()(i));
        __asm__ __volatile__("");
    }
    s = h;
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << elapsed_seconds.count() << "s\n";
}
int main()
{

    test_ck();
    test_phmap();
}