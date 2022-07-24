//
// Created by MacBook Pro on 23.07.2022.
//
#include <stdlib.h>

const STOP_GROWTH_SIZE = 4096;
typedef struct {
    u_int64_t len;
    u_int64_t cap;
    uintptr_t ptr;
    size_t size;
} Slice;

Slice *make(u_int64_t cap, size_t size) {
    uintptr_t ptr = (uintptr_t) malloc(cap * size);
    Slice *sl = malloc(sizeof(Slice));
    sl->ptr = ptr;
    sl->cap = cap;
    sl->len = 0;
    sl->size = size;
    return sl;
}

Slice *append(Slice *src, uintptr_t val) {
    u_int64_t next_len = src->len + 1;
    u_int64_t len_int_bytes = src->len * src->size;
    if (next_len > src->cap) {
        u_int64_t next_cap = src->cap * 2;
        if (next_cap == 0) {
            next_cap = 2;
        }

        if (next_cap > STOP_GROWTH_SIZE) {
            next_cap = src->cap + 100;
        }

        char *next_ptr = (char *) malloc(next_cap * src->size);
        char *prev_ptr = (char *) src->ptr;
        for (u_int64_t i = 0; i < len_int_bytes; ++i) {
            next_ptr[i] = prev_ptr[i];
        }
        char *val_ptr = (char *) val;
        for (u_int64_t i = len_int_bytes; i < len_int_bytes + (src->size); ++i) {
            next_ptr[i] = val_ptr[i - len_int_bytes];
        }
        src->cap = next_cap;
        src->len = next_len;
        src->ptr = (uintptr_t) next_ptr;
        free(prev_ptr);
        return src;
    }
    char *ptr = (char *) src->ptr;
    char *val_ptr = (char *) val;
    for (u_int64_t i = len_int_bytes; i < len_int_bytes + (src->size); ++i) {
        ptr[i] = val_ptr[i - len_int_bytes];
    }
    src->len = next_len;
    return src;
}


uintptr_t get(Slice *src, u_int64_t idx) {
    if (idx >= src->len) {
        return (uintptr_t) NULL;
    }
    return src->ptr + (idx * src->size);
}

uintptr_t set(Slice *src, u_int64_t idx, uintptr_t val) {
    if (idx >= src->len) {
        return (uintptr_t) NULL;
    }

    u_int64_t start_len_int_bytes = idx * src->size;
    char *ptr = (char *) src->ptr;
    char *val_ptr = (char *) val;
    for (u_int64_t i = start_len_int_bytes; i < start_len_int_bytes + (src->size); ++i) {
        ptr[i] = val_ptr[i - start_len_int_bytes];
    }
    return 1;
}

void mem_free(Slice *src) {
    free((void *) src->ptr);
    free(src);
}



