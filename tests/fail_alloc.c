/* Exercise the reader's initial allocation and growth failure paths. */
#include <stdio.h>
#include <stdlib.h>

static void *test_realloc(void *ptr, size_t size)
{
    static int calls;
    const char *fail_at = getenv("FAIL_AT");
    if (fail_at != NULL && ++calls == atoi(fail_at))
        return NULL;
    return realloc(ptr, size);
}

#define realloc test_realloc
#include "../reading_cow.c"
