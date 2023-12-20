#include <iostream>
#include <jemalloc/jemalloc.h>
#include <malloc.h>
#include <string.h>
#include <sys/mman.h>

int main() {
    int epoch = 1;
    for (auto i = 0ul; i < 100000; ++i) {
        void* ptr = 0;
        int ret = posix_memalign(&ptr, 16, 100000);
        size_t sz, allocated, active, metadata, resident, mapped;
        sz = sizeof(size_t);
        mallctl("thread.tcache.flush", NULL, NULL, NULL, 0);
        mallctl("epoch", NULL, NULL, &epoch, sizeof(epoch));
        if (mallctl("stats.allocated", &allocated, &sz, NULL, 0) == 0
            && mallctl("stats.active", &active, &sz, NULL, 0) == 0
            && mallctl("stats.metadata", &metadata, &sz, NULL, 0) == 0
            && mallctl("stats.resident", &resident, &sz, NULL, 0) == 0
            && mallctl("stats.mapped", &mapped, &sz, NULL, 0) == 0) {
            fprintf(stderr,
                "Current allocated/active/metadata/resident/mapped: %zu/%zu/%zu/%zu/%zu\n",
                allocated, active, metadata, resident, mapped);
        }
    }
}
