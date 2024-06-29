/* coding:utf-8
 * Copyright (C) dirlt
 */

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <random>

//// diff  clang++-15 -O3 memory_order2.cpp -lpthread
//// with g++
std::atomic<int> flag{0};
uint64_t share_val{};
  std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dist{100, 500};

void IncsharedXTimeNoAcquire()
{
    for (int count{0}; count < 10000000;)
    {
        int expect{};
        if (flag.compare_exchange_strong(expect, 1, std::memory_order_acquire))
        {
            share_val ++;
            count ++;
            flag.store(0, std::memory_order_release);
        }
    }
}

int main() {

    // start thread.
    std::thread _t0(IncsharedXTimeNoAcquire);
    std::thread _t1(IncsharedXTimeNoAcquire);
        std::thread _t3(IncsharedXTimeNoAcquire);
    std::thread _t2(IncsharedXTimeNoAcquire);
    _t0.join();
    _t1.join();
        _t2.join();
    _t3.join();
    std::cout << "shared:" << share_val << "\n";
    return 0;
}