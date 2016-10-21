# Variable Sized Array With Variable Sized Items
---

## How to Use
```c
varr_t *arr = varr_init();
int test = 8; // Important: you need to pass pointers to varr_* functions.

varr_push(arr, &test, sizeof(int)); // Adds to the end of the array.
varr_unshift(arr, &test, sizeof(int)); // Adds to the beginnin of the array.
int test2 = *((int *) varr_shift(arr)); // Removes the first item of the array and returns it.
int test3 = *((int *) varr_pop(arr)); // Removes the first item of the array and returns it.

varr_destroy(arr); // Frees memory used by the array.
```

Macros coming soon.
