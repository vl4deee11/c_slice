#include <stdio.h>
#include "slice.h"


int main() {
    printf("INT TYPE\n");
    Slice *sl = make(15, sizeof(int));
    for (int i = 0; i < 15; ++i) {
        sl = append(sl, (uintptr_t) & i);
    }

    for (int i = 0; i < 15; ++i) {
        int *x0 = (int *) get(sl, i);
        printf("BEFORE=%d\n", *x0);

        int zi = i + 10;
        set(sl, i, (uintptr_t) & zi);
        x0 = (int *) get(sl, i);
        printf("AFTER=%d\n", *x0);
    }

    mem_free(sl);

    printf("SLICE OF SLICE TYPE\n");
    Slice *slsl = make(0, sizeof(Slice *));
    for (int i = 0; i < 15; ++i) {
        Slice *sli = make(0, sizeof(int));
        for (int j = 0; j < 15; ++j) {
            int k = j + i;
            sli = append(sli, (uintptr_t) & k);
        }
        slsl = append(slsl, (uintptr_t) & sli);
    }

    for (int i = 0; i < 15; ++i) {
        Slice **psli = (Slice **) get(slsl, i);
        Slice *sli = *psli;
        printf("SLICE %d\n", i);
        for (int j = 0; j < 15; ++j) {
            int *x0 = (int *) get(sli, j);
            printf("BEFORE=%d\n", *x0);

            int zi = *x0 + 10;
            set(sli, j, (uintptr_t) & zi);

            int *x1 = (int *) get(sli, j);
            printf("AFTER=%d\n", *x1);
        }
        mem_free(sli);
    }

    mem_free(slsl);

    printf("STR TYPE\n");

    Slice *slstr = make(0, sizeof(char *));
    for (int i = 0; i < 15; ++i) {
        char *xxx = "123456";
        slstr = append(slstr, (uintptr_t) xxx);
    }

    for (int i = 0; i < 15; ++i) {
        char *xxx = (char *) get(slstr, i);
        printf("BEFORE=");
        for (int j = 0; j < 6; ++j) {
            printf("%c", xxx[j]);
        }
        printf("\n");

        char *xxx2 = "ABCDEF";
        set(slstr, i, (uintptr_t) xxx2);
        xxx = (char *) get(slstr, i);
        printf("AFTER=");
        for (int j = 0; j < 6; ++j) {
            printf("%c", xxx[j]);
        }
        printf("\n");

    }

    mem_free(slstr);

    printf("FLOAT TYPE\n");
    Slice *slfl = make(15, sizeof(float));
    for (int i = 0; i < 15; ++i) {
        float ii = i + 10.67f;
        sl = append(slfl, (uintptr_t) & ii);
    }

    for (int i = 0; i < 15; ++i) {
        float *x0 = (float *) get(sl, i);
        printf("BEFORE=%f\n", *x0);

        float zi = i + 5.5f;
        set(sl, i, (uintptr_t) & zi);
        x0 = (float *) get(sl, i);
        printf("AFTER=%f\n", *x0);
    }

    mem_free(slfl);

    return 0;
}




