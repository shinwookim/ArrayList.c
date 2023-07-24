#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stddef.h>
#include <stdbool.h>
/********
 * Data *
 ********/
#define DEFAULT_CAPACITY 10
typedef struct
{
    size_t size;         // number of elements currently in the list
    size_t capacity;     // maximum number of elements that fit in current allocated memory
    size_t element_size; // size of each element
    void *data;          // pointer to allocated memory
} ArrayList;

/**************
 * Operations *
 **************/
ArrayList *ArrayList_new(size_t element_size);
void ArrayList_free(ArrayList *list);
size_t ArrayList_size(ArrayList *list);
bool ArrayList_isEmpty(ArrayList *list);
void ArrayList_trimToSize(ArrayList *list);
void ArrayList_ensureCapacity(ArrayList *list, size_t min_capacity);
bool ArrayList_add(ArrayList *AL, size_t index, void *E);
bool ArrayList_append(ArrayList *AL, void *E);
bool ArrayList_remove(ArrayList *AL, size_t index);
void *ArrayList_get(ArrayList *AL, size_t index);
#endif /* ARRAYLIST_H */