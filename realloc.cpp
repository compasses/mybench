#include<iostream>
#include<thread>
#include<chrono>
#include<cstring>
#include <jemalloc/jemalloc.h>

void statsPrint(void *result, const char *str) {
    printf("%s",str);
}

int main(int argc, char ** argv)
{
    size_t SIZE = 1024L * 1024 * 1024 * 8;
    size_t SIZE2 = 1024L * 1024 * 512;
    using namespace std::chrono_literals;
    std::cout << "before realloc" << std::endl;
    std::this_thread::sleep_for(10s);
    char * chars = nullptr;
    chars = (char*)::realloc(chars, SIZE);
    std::cout << "alloc finished, ptr: " << static_cast<void*>(chars) << std::endl;
    std::this_thread::sleep_for(10s);
    malloc_stats_print(statsPrint, NULL, NULL);
    // memset(chars, 0, SIZE);
    // std::cout << "memset finished, ptr: " << static_cast<void*>(chars) << std::endl;
    // std::this_thread::sleep_for(30s);
    // chars = (char*)::realloc(chars, SIZE2);
    // std::cout << "realloc finished, ptr: " << static_cast<void*>(chars) << std::endl;
    // std::this_thread::sleep_for(30s);
}