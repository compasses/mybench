#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jemalloc/jemalloc.h>


int jemalloc_purge() {
    char tmp[32];
    unsigned narenas = 0;
    size_t sz = sizeof(unsigned);
    if (!mallctl("arenas.narenas", &narenas, &sz, NULL, 0)) {
        sprintf(tmp, "arena.%d.purge", narenas);
        if (!mallctl(tmp, NULL, 0, NULL, 0)) {
            return 1;
        }
    }
    return 0;
}


void statsPrint(void *result, const char *str) {
    printf("%s",str);
}

void main(void) {
    int j;
    for(j=0; j<3000; j++) {
        void* p = malloc(1000000);
        memset(p, 0, 1000000);
    }
    jemalloc_purge();
    malloc_stats_print(statsPrint, NULL, NULL);
}