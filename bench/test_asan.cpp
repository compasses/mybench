// example1.cpp
// use-after-poison error
#include <stdlib.h>

// /usr/bin/clang++-15 -fuse-ld=mold  -g -fno-omit-frame-pointer -fsanitize-recover=all -ferror-limit=0 -DSANITIZER -fsanitize=address -fsanitize-address-use-after-scope -fdiagnostics-color=always -fsized-deallocation -fno-omit-frame-pointer  -gdwarf-aranges -pipe -mssse3 -msse4.1 -msse4.2 -mpclmul -mpopcnt -fasynchronous-unwind-tables -falign-functions=32   -Wall -Wno-unused-command-line-argument  -fdiagnostics-absolute-paths -fexperimental-new-pass-manager  -O2 -g -DNDEBUG -O1  -fno-pie test_asan.cpp

extern "C" void __asan_poison_memory_region(void *, size_t);

int main(int argc, char **argv) {
    char *x = new char[16];
    x[10] = 0;
    __asan_poison_memory_region(x, 16);

    int res = x[argc * 10];              // Boom!
 
    delete [] x;
    return res;
}