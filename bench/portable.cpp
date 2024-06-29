#include <vector>
#include <thread>
#include <iostream>

struct S
{
    ~S() { std::cerr << "\t\nThread exited\n"; }
};

thread_local S s;

int main(int, char **)
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; ++i)
        threads.emplace_back([]{ std::cerr << &s << "\n"; });

    for (auto & thread : threads)
        thread.join();

    return 0;
}