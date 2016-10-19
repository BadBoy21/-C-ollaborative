#ifndef _VAR_ARRAY_H
#define _VAR_ARRAY_H 1

#define VAR_ARRAY_MAX_SIZE 512

typedef struct {
    int size;
    int bytes;
    int *positions;
    void *items;
} varr_t;

varr_t* varr_init();

void* varr_get(varr_t *array, int index);

void varr_push(varr_t *array, void *item, int length);
void varr_unshift(varr_t *array, void *item, int length);
void* varr_pop(varr_t *array);
void* varr_shift(varr_t *array);

void varr_destroy(varr_t *array);

#endif // _VAR_ARRAY_H
