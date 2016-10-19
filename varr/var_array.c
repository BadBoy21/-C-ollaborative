#include <stdlib.h>
#include "var_array.h"

varr_t* varr_init() {
    varr_t *array = malloc(sizeof(varr_t));
    array->size = 0;
    array->bytes = 0;
    array->positions = malloc(sizeof(int));
    array->items = malloc(sizeof(int));
    return array;
}

void* varr_get(varr_t *array, int index) {
    if (index > array->size || index < 0)
        return NULL;
    return *(array->items + array->positions[index]);
}

void varr_push(varr_t *array, void *item, int length) {
    // Do not do anything if the array has reached maximum size.
    if (array->size == VAR_ARRAY_MAX_SIZE)
        return;
   
    // Increase the size of the items pointer for the new item.
    void *new_items = realloc(array->items, array->bytes + length);
    if (new_items != array->items)
        // Pointer location changed. Free the old pointer
        free(array->items);
   
    // Copy length bytes from item to our new empty space.
    memcpy(new_items + array->bytes, item, length);
    // Move the new pointer to the old one's place.
    array->items = new_items;

    // Increase the size of the positions array.
    int *new_positions = realloc(array->positions, (array->size + 1) * sizeof(int));
    if (new_positions != array->positions)
        // Pointer location changed. Free the old pointer
        free(array->positions);
    
    // Add location of the new item to the positions array.
    new_positions[array->size] = array->bytes;

    // Move the new pointer to the old one's place.
    array->positions = new_positions;

    // Increase size and byte members.
    array->size += 1;
    array->bytes += length;

    return;
}

void varr_unshift(varr_t *array, void *item, int length) {
    // Unshifting is a bit trickier. We have to create a new array,
    // move the contents to length bytes after its start 
    // and then put in the item.

    if (array->size == VAR_ARRAY_MAX_SIZE)
        return;

    void *new_items = malloc(array->bytes + length);
    memcpy(new_items + length, array->items, array->bytes);
    memcpy(new_items, item, length);
    free(array->items);
    array->items = new_items;

    int *new_positions = malloc((array->size + 1) * sizeof(int));
    memcpy(new_positions + sizeof(int), array->positions, array->size);
    new_positions[0] = 0;
    for (int i = 1; i < array->size; i++)
        new_positions[i] += length;
    free(array->positions);
    array->positions = new_positions;

    array->size += 1;
    array->bytes += length;

    return;
}

void* varr_pop(varr_t *array) {
    // Check for incorrect sizes.
    if (array->size == 0)
        return NULL;

    // Get the length of the item we are popping.
    int length = array->bytes - array->positions[array->size - 1];

    // Reserve space for the item we are popping.
    void *item = malloc(length);

    // Copy the item from the array to our malloc'd variable.
    memcpy(item, array->items + array->positions[array->size - 1], length);

    // Shrink the items and positions arrays.
    void *new_items     = realloc(array->items, array->bytes - length);
    int  *new_positions = realloc(array->positions, (array->size - 1) * sizeof(int));

    // No need to compare the old and new pointers, since we shrinked them they will not be moved.
    array->items     = new_items;
    array->positions = new_positions;

    // Decrease the size and bytes members.
    array->size -= 1;
    array->bytes -= length;

    // Return the popped item.
    return item;
}

