#include <string.h>
#include <stdlib.h>
#include "var_array.h"

varr_t* varr_init() {
    varr_t *array = malloc(sizeof(varr_t));
    array->size = 0;
    array->bytes = 0;
    array->positions = malloc(4);
    array->items = malloc(4);
    return array;
}

void* varr_get(varr_t *array, int index) {
    if (index > array->size || index < 0)
        return NULL;
    return (void *) array->items + array->positions[index];
}

void varr_push(varr_t *array, void *item, int length) {
    // Do not do anything if the array has reached maximum size.
    if (array->size == VAR_ARRAY_MAX_SIZE)
        return;
   
    // Increase the size of the items pointer for the new item.
    void *new_items = realloc(array->items, array->bytes + length);
   
    // Copy length bytes from item to our new empty space.
    memcpy((void *) new_items + array->bytes, item, length);
    // Move the new pointer to the old one's place.
    array->items = new_items;

    // Increase the size of the positions array.
    int *new_positions = realloc(array->positions, (array->size + 1) * sizeof(int));
    
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
    // and then put in the item to the beginning.

    if (array->size == VAR_ARRAY_MAX_SIZE)
        return;

    // Allocate a new memory arrea for all the items + the new item.
    void *new_items = malloc(array->bytes + length);
    // Copy the old items length bytes after the start.
    memcpy((void *) new_items + length, array->items, array->bytes);
    // Copy the new item to the beginning.
    memcpy(new_items, item, length);
    // Free the old array.
    free(array->items);
    // Point the items member to the new array.
    array->items = new_items;

    // Create a new positions array.
    int *new_positions = malloc((array->size + 1) * sizeof(int));
    // Copy the old position list to 1 int after the new array.
    memcpy((int *) (new_positions + 1), array->positions, array->size * sizeof(int));
    new_positions[0] = 0;
    // Increase all positions by length.
    for (int i = 1; i <= array->size; i++)
        new_positions[i] += length;

    // Free the old array.
    free(array->positions);
    // Point the positions member to the new array.
    array->positions = new_positions;

    // Increase ths size and bytes members.
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

void* varr_shift(varr_t *array) {
    // Check for incorrect sizes.
    if (array->size == 0)
        return NULL;

    // Get the length of the item we are shifting, which is equal to the position of the second item.
    int length = array->positions[1];

    // Reserve space for the item we are shifting.
    void *item = malloc(length);

    // Copy the item from the array to our malloc'd variable.
    memcpy(item, array->items, length);

    // Allocate new space for our arrays.
    void *new_items     = malloc(array->bytes - length);
    int  *new_positions = malloc((array->size - 1) * sizeof(int));

    // Copy all items offsetted by the first item to the new arrays.
    memcpy(new_items, array->items + length, array->bytes - length);
    memcpy(new_positions, array->positions + 1, (array->size - 1) * sizeof(int));

    // Decrease ("move back") all positions by length.
    for (int loop = 0; loop < array->size-1; loop++)
        new_positions[loop] -= length;

    // Free the old pointers.
    free(array->items);
    free(array->positions);

    array->items     = new_items;
    array->positions = new_positions;

    // Decrease the size and bytes members.
    array->size -= 1;
    array->bytes -= length;

    // Return the popped item.
    return item;
}

void varr_destroy(varr_t *array) {
    free(array->items);
    free(array->positions);
    free(array);
}
