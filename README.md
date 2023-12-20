# mybench
g++ bench_hash.cpp -std=c++17  -lbenchmark -lpthread -O3 -o bench_hash
g++ bench_alloc.cpp -std=c++17  -I../include -L../lib -lbenchmark -lpthread -ljemalloc -o bench_alloc