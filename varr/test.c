#include <stdio.h>
#include <stdint.h>
#include "var_array.h"

int test();

int main(int argc, char **argv) {
    printf("\x1b[32mStarting test\x1b[0m\n");
    return test();
}

int test() {
    printf("\x1b[32mInitializing an instance\x1b[0m\n");
    varr_t *arr = varr_init();
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[34mPushing items\x1b[0m\n");
    for (int i = 0; i < 5; i++) {
        varr_push(arr, &i, sizeof(int));
        printf("\x1b[34mPushed %d\x1b[0m\n", i);
        printf("array->bytes: %d\narray->size: %d\narray->positions[-1]: %d\n", arr->bytes, arr->size, arr->positions[arr->size - 1]);
    }
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[34mvarr_get(3) testing...\x1b[0m\n");
    printf("%d\n", *((int*) varr_get(arr, 3)));
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[34mvarr_pop testing...\x1b[0m\n");
    for (int j = 0; j < 2; j++)
        printf("Popped %d\n", *((int *) varr_pop(arr)));
    printf("Array size is now %d.\n", arr->size);
    printf("Array is now %d bytes.\n", arr->bytes);
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[34mTesting varr_unshift...\x1b[0m\n");
    int temp = 18;
    varr_unshift(arr, &temp, sizeof(int));
    printf("\x1b[34mCalled varr_unshift(arr, &temp, sizeof(int))\x1b[0m\n");
    printf("varr_get(0) is %d\n", *((int *) varr_get(arr, 0)));
    printf("Array size is now %d.\n", arr->size);
    printf("Array is now %d bytes.\n", arr->bytes);
    printf("\x1b[32mDone.\x1b[0m\n");
    // Sanity check
    for (int z = 0; z < arr->size; z++) {
        printf("%d ", arr->positions[z]);
    }
    printf("\n");

    printf("\x1b[34mTesting pushing different sized items...\x1b[0m\n");
    uint16_t test1 = 16;
    uint32_t test2 = 8282728;
    uint64_t test3 = 93939292727;
    varr_push(arr, &test1, sizeof(uint16_t));
    printf("Pushed uint16_t\x1b[0m\n");
    printf("Array size is now %d.\n", arr->size);
    printf("Array is now %d bytes.\n", arr->bytes);
    varr_push(arr, &test2, sizeof(uint32_t));
    printf("Pushed uint32_t\x1b[0m\n");
    printf("Array size is now %d.\n", arr->size);
    printf("Array is now %d bytes.\n", arr->bytes);
    varr_push(arr, &test3, sizeof(uint64_t));
    printf("Pushed uint64_t\x1b[0m\n");
    printf("Array size is now %d.\n", arr->size);
    printf("Array is now %d bytes.\n", arr->bytes);
    printf("\x1b[34mAttempting to pop items...\x1b[0m\n");
    printf("Pulled uint64_t: %llu\x1b[0m\n", *((uint64_t *) varr_pop(arr)));
    printf("Pulled uint32_t: %d\x1b[0m\n", *((uint32_t *) varr_pop(arr)));
    printf("Pulled uint16_t: %d\x1b[0m\n", *((uint16_t *) varr_pop(arr)));
    printf("Array size is now %d.\n", arr->size);
    printf("Array is now %d bytes.\n", arr->bytes);
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[34mShifting 3 items...\x1b[0m\n");
    for (int k = 0; k < 3; k++) {
        printf("Shifted %d", *((int *) varr_shift(arr)));
        printf("Array size is now %d.\n", arr->size);
        printf("Array is now %d bytes.\n", arr->bytes);
    }
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[34mFreeing memory used by array...\x1b[0m\n");
    varr_destroy(arr);
    printf("\x1b[32mDone.\x1b[0m\n");
    printf("\x1b[32mTest successful. \x1b[0m\n");
    return 0;
}

