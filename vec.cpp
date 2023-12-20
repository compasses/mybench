#include<stdlib.h>

void plus(int64_t * __restrict a, int64_t * __restrict b, int64_t * __restrict c, size_t size)
{
   for (size_t i = 0; i < size; ++i) {
       c[i] = b[i] + a[i];
   }
}
///$ /usr/bin/clang++-15 -mavx2 -fno-unroll-loops -O3 -S vectorization_example.cpp
