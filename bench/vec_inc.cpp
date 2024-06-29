#include <cstdint>
#include <iostream>
#include <vector>

void __attribute__ ((noinline)) vector8_inc(std::vector<uint8_t>& __restrict v) {
    for (size_t i = 0; i < v.size(); i++) {
        v[i]++;
    }
}

void __attribute__ ((noinline)) vector32_inc(std::vector<uint32_t>& __restrict v) {
    for (size_t i = 0; i < v.size(); i++) {
        v[i]++;
    }
}



int main()
{
    std::vector<uint32_t> a(200000);
    std::vector<uint8_t> b(200000);

    vector32_inc(a);
    vector8_inc(b);

    auto x = a[10] + b[2000];
    std::cout << x << "\n";

    return 0;
}