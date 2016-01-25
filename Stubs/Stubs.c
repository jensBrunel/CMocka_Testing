#include <stdint.h>
#include "Stubs.h"
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "cmocka.h"


void* __real_malloc (size_t __size);

/**
 * This function wraps the real malloc
 */
void* __wrap_malloc (size_t __size)
{
    void *lptr = __real_malloc(__size);
    printf("\nMalloc: %d bytes %p\n", __size, lptr);
    return lptr;
}

void __real_free (void *__ptr);

/**
 * This function wraps the real free
 */
void __wrap_free(void *__ptr)
{
   printf("Free: %p address\n", __ptr);
   __real_free(__ptr);
}

int __real_memcmp (const void *__s1, const void *__s2, size_t __n);

/*Flag to trigger wrapped code*/
bool useWrapped = false;
/**
 * This function wraps the real memcpy.
 * The useWrapped flag will cause the return of a mocked value.
 */
int __wrap_memcmp (const void *__s1, const void *__s2, size_t __n)
{
   int result = 0;
    if(useWrapped)
    {
        result = (int)mock();
    }
    else
    {
    printf("cmp: %p with %p, size is %i\n", __s1, __s2, __n);
    result = __real_memcmp(__s1, __s2, __n);
    }
    return result;
}
