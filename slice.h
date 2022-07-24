//
// Created by MacBook Pro on 23.07.2022.
//

#include <stdlib.h>

#ifndef slice_h
#define slice_h
typedef struct {
    u_int64_t len;
    u_int64_t cap;
    uintptr_t ptr;
    size_t size;
} Slice;

Slice *make(u_int64_t cap, size_t size);

Slice *append(Slice *src, uintptr_t val);

uintptr_t get(Slice *src, u_int64_t idx);

uintptr_t set(Slice *src, u_int64_t idx, uintptr_t val);

void mem_free(Slice *src);

void print(Slice *src);

#endif //slice_h


