#include "libArrayList.h"
#include <stdbool.h>
#include <assert.h>
ArrayList *ArrayList_new()
{
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list) // check malloc success for list
    {
        list->size = 0;                    // list initially empty
        list->capacity = DEFAULT_CAPACITY; // DEFAULT_CAPACITY = 10
        list->data = (void **)malloc(DEFAULT_CAPACITY * sizeof(void *));
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
    void *const new_data = realloc(list->data, (list->size * sizeof(void *)));
    assert(new_data != NULL); // check for malloc fail
    list->data = new_data;
    list->capacity = list->size;
}

void ArrayList_ensureCapacity(ArrayList *list, size_t min_capacity)
{
    assert(list != NULL); // ensure parameterized AL is valid
    size_t new_capacity = list->capacity;
    while (new_capacity < min_capacity)
    {
        // based on Java 8's resizing policy
        new_capacity = new_capacity + (new_capacity >> 1) + 1; // (+1) in case new_capacity == 0
        assert(new_capacity >= list->capacity);                // check for overflows
    }
    void *new_data = realloc(list->data, (new_capacity * sizeof(void *)));
    assert(new_data != NULL); // check for malloc fail
    list->data = new_data;
    list->capacity = new_capacity;
}

bool ArrayList_add(ArrayList *AL, size_t index, const void *E)
{
    assert(AL != NULL);        // ensure parameterized AL is valid
    assert(index > 0);         // ensure parameterized index is valid
    assert(index <= AL->size); // ensure parameterized index is valid
    assert(E != NULL);         // ensure parameterized E is valid
    AL->data[index] = E;
    return true;
}

bool ArrayList_append(ArrayList *AL, const const void *E)
{
    assert(AL != NULL); // ensure parameterized AL is valid
    assert(E != NULL);  // ensure parameterized E is valid
    return ArrayList_add(AL, AL->size, E);
}

bool *ArrayList_remove(ArrayList *AL, size_t index)
{
    assert(AL != NULL);       // ensure parameterized AL is valid
    assert(index > 0);        // ensure parameterized index is valid
    assert(index < AL->size); // ensure parameterized index is valid

    void **dest = &(AL->data[index]);
    void **src = &(AL->data[index + 1]);
    free(*dest); // deallocate to prevent memory leaks and invalid references
    /* shift the rest of the list to remove item in AL->data[index] */
    int i = index + i;
    while (i < AL->size)
    {
        *dest = *src;
        i++, dest++, src++;
    }
    AL->size--;
    return true;
}

void *ArrayList_get(ArrayList *AL, size_t index)
{
    assert(AL != NULL);       // ensure parameterized AL is valid
    assert(index > 0);        // ensure parameterized index is valid
    assert(index < AL->size); // ensure parameterized index is valid
    return AL->data[index];
}
