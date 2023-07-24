#include "libArrayList.h"
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

void malloc_fail(char *what, char *where)
{
    printf("Error: %s in %s could not be allocated\n", what, where);
}

void test_init_state()
{
    ArrayList *list = ArrayList_new(sizeof(uint32_t));
    if (list)
    {
        assert(ArrayList_size(list) == 0);
        assert(ArrayList_isEmpty(list));
        ArrayList_free(list);
    }
    else
        malloc_fail("ArrayList", "test_init_state");
}

void test_size_change()
{
    ArrayList *list = ArrayList_new(sizeof(uint32_t));
    if (list)
    {
        // ArrayList initially empty
        assert(ArrayList_size(list) == 0);
        assert(ArrayList_isEmpty(list));

        uint32_t element = 0;
        ArrayList_add(list, 0, &element);
        assert(ArrayList_size(list) == 1);
        assert(!ArrayList_isEmpty(list));

        ArrayList_add(list, 0, &element);
        assert(ArrayList_size(list) == 2);
        assert(!ArrayList_isEmpty(list));

        ArrayList_append(list, &element);
        assert(ArrayList_size(list) == 3);
        assert(!ArrayList_isEmpty(list));

        ArrayList_remove(list, 2);
        assert(ArrayList_size(list) == 2);
        assert(!ArrayList_isEmpty(list));

        ArrayList_remove(list, 0);
        assert(ArrayList_size(list) == 1);
        assert(!ArrayList_isEmpty(list));

        ArrayList_remove(list, 0);
        assert(ArrayList_size(list) == 0);
        assert(ArrayList_isEmpty(list));

        ArrayList_free(list);
    }
    else
        malloc_fail("ArrayList", "test_size_change");
}

void test_append_remove()
{
    ArrayList *list = ArrayList_new(sizeof(uint32_t));

    if (list)
    {
        uint32_t element;

        element = 0;
        ArrayList_add(list, 0, &element);
        assert(*(uint32_t *)ArrayList_get(list, 0) == 0);

        element = 10;
        ArrayList_append(list, &element);
        assert(*(uint32_t *)ArrayList_get(list, 0) == 0);
        assert(*(uint32_t *)ArrayList_get(list, 1) == 10);

        element = 12;
        ArrayList_add(list, 1, &element);
        assert(*(uint32_t *)ArrayList_get(list, 0) == 0);
        assert(*(uint32_t *)ArrayList_get(list, 1) == 12);
        assert(*(uint32_t *)ArrayList_get(list, 2) == 10);

        ArrayList_remove(list, 1);
        assert(*(uint32_t *)ArrayList_get(list, 0) == 0);
        assert(*(uint32_t *)ArrayList_get(list, 1) == 10);

        ArrayList_remove(list, 0);
        assert(*(uint32_t *)ArrayList_get(list, 0) == 10);

        ArrayList_free(list);
    }
    else
        malloc_fail("ArrayList", "test_append_remove");
}

int main()
{
    test_init_state();
    puts("test_init_state successful.");

    test_size_change();
    puts("test_size_change successful.");

    test_append_remove();
    puts("test_append_remove successful.");

    return 0;
}
