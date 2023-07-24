#include "libArrayList.h"
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
ArrayList *ArrayList_new(size_t element_size)
{
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list) // check malloc success for list
    {
        list->size = 0;                    // list initially empty
        list->capacity = DEFAULT_CAPACITY; // DEFAULT_CAPACITY = 10
        list->data = (void **)malloc(DEFAULT_CAPACITY * sizeof(void *));
        list->element_size = element_size;
        if (!list->data) // check malloc fail for list->data
        {
            free(list);
            list = NULL;
        }
    }
    return list; // list == NULL on malloc fail
}

void ArrayList_free(ArrayList *list)
{
    assert(list != NULL); // ensure parameterized list is valid
    free(list->data);
    free(list);
}

size_t ArrayList_size(ArrayList *list)
{
    assert(list != NULL); // ensure parameterized list is valid
    return list->size;
}
bool ArrayList_isEmpty(ArrayList *list)
{
    assert(list != NULL); // ensure parameterized list is valid
    return (list->size == 0) ? true : false;
}

void ArrayList_trimToSize(ArrayList *list)
{
    assert(list != NULL); // ensure parameterized list is valid
    void *const new_data = realloc(list->data, (list->size * list->element_size));
    assert(new_data != NULL); // check for malloc fail
    list->data = new_data;
    list->capacity = list->size;
}

void ArrayList_ensureCapacity(ArrayList *list, size_t min_capacity)
{
    assert(list != NULL); // ensure parameterized list is valid
    size_t new_capacity = list->capacity;
    while (new_capacity < min_capacity)
    {
        // based on Java 8's resizing policy
        new_capacity = new_capacity + (new_capacity >> 1) + 1; // (+1) in case new_capacity == 0
        assert(new_capacity >= list->capacity);                // check for overflows
    }
    void *new_data = realloc(list->data, (new_capacity * list->element_size));
    assert(new_data != NULL); // check for malloc fail
    list->data = new_data;
    list->capacity = new_capacity;
}

bool ArrayList_add(ArrayList *list, size_t index, void *E)
{
    assert(list != NULL);        // ensure parameterized list is valid
    assert(index >= 0);          // ensure parameterized index is valid
    assert(index <= list->size); // ensure parameterized index is valid
    assert(E != NULL);           // ensure parameterized E is valid

    char *index_ptr = (char *)list->data + (index * list->element_size);
    // Valid call even for append case (list->size - index == 0)
    memmove(index_ptr + list->element_size, index_ptr, list->element_size * (list->size - index)); // shift right by one element
    memcpy(index_ptr, E, list->element_size);
    list->size++;
    return true;
}

bool ArrayList_append(ArrayList *AL, void *E)
{
    assert(AL != NULL); // ensure parameterized AL is valid
    assert(E != NULL);  // ensure parameterized E is valid
    return ArrayList_add(AL, AL->size, E);
}

bool ArrayList_remove(ArrayList *list, size_t index)
{
    assert(list != NULL);       // ensure parameterized list is valid
    assert(index >= 0);         // ensure parameterized index is valid
    assert(index < list->size); // ensure parameterized index is valid

    char *index_ptr = (char *)list->data + (index * list->element_size);
    memmove(index_ptr, index_ptr + list->element_size, (list->size - index + 1) * list->element_size);
    list->size--;
    return true;
}

void *ArrayList_get(ArrayList *list, size_t index)
{
    assert(list != NULL);       // ensure parameterized AL is valid
    assert(index >= 0);         // ensure parameterized index is valid
    assert(index < list->size); // ensure parameterized index is valid
    return list->data + (index * list->element_size);
}
