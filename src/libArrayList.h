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

/**
 * @brief Constructs an empty list with an initial capacity of ten.
 *
 * @param element_size size of each element to be stored in the list.
 * @return The pointer to the ArrayList struct.
 */
ArrayList *ArrayList_new(size_t element_size);

/**
 * @brief Destructs the list by freeing alloacted memory.
 *
 * @param list - a pointer to an ArrayList.
 */
void ArrayList_free(ArrayList *list);

/**
 * @brief Returns the number of elements in this list.
 *
 * @param list - a pointer to an ArrayList.
 * @return The number of elements currently in the array.
 */
size_t ArrayList_size(ArrayList *list);

/**
 * @brief Returns true if this list contains no elements.
 *
 * @param list - a pointer to an ArrayList.
 * @return true if this list contains no elements.
 * @return false if this list contains at least one element.
 */
bool ArrayList_isEmpty(ArrayList *list);

/**
 * @brief Trims the capacity of this ArrayList instance to be the list's current size.
 *        An application can use this operation to minimize the storage of an ArrayList instance.
 *
 * @param list - a pointer to an ArrayList.
 */
void ArrayList_trimToSize(ArrayList *list);

/**
 * @brief Increases the capacity of this ArrayList instance, if necessary, to
 *        ensure that it can hold at least the number of elements specified by the
 *        minimum capacity parameter.
 *
 * The resulting list will have the size calculated Java 8-like
 * dynamic resizing policy (that is greater than the minimum capacity parameter).
 *
 * @param list - a pointer to an ArrayList.
 * @param min_capacity - the desired minimum capacity.
 */
void ArrayList_ensureCapacity(ArrayList *list, size_t min_capacity);

/**
 * @brief Inserts the specified element at the specified position in this list.
 *        Shifts the element currently at that position (if any) and
 *        any subsequent elements to the right (adds one to their indices).
 *
 * @param list - a pointer to an ArrayList.
 * @param index - index at which the specified element is to be inserted
 * @param E - pointer to the element to be inserted
 * @return true on sucess
 * @return false on fail
 */
bool ArrayList_add(ArrayList *list, size_t index, void *E);

/**
 * @brief Appends the specified element to the end of this list.
 *
 * @param list - a pointer to an ArrayList.
 * @param E - element to be appended to this list
 * @return true on sucess
 * @return false on fail
 */
bool ArrayList_append(ArrayList *list, void *E);

/**
 * @brief Removes the element at the specified position in this list. Shifts any subsequent elements to the left (subtracts one from their indices).

 *
 * @param list - a pointer to an ArrayList.
 * @param index - the index of the element to be removed
 * @return true on sucess
 * @return false on fail
 */
bool ArrayList_remove(ArrayList *list, size_t index);

/**
 * @brief Returns the element at the specified position in this list.
 *
 * @param list - a pointer to an ArrayList.
 * @param index - index of the element to return
 * @return the element at the specified position in this list
 */
void *ArrayList_get(ArrayList *list, size_t index);

#endif /* ARRAYLIST_H */