#include <stdint.h>
#include "Stubs.h"
#include <stdio.h>
#include <stdlib.h>


void* __real_malloc (size_t __size);

/* This function wraps the real malloc */
void* __wrap_malloc (size_t __size)
{
    void *lptr = __real_malloc(__size);
    printf("\nMalloc: %d bytes %p\n", __size, lptr);
    return lptr;
}

void __real_free (void *__ptr);

void __wrap_free(void *__ptr)
{
   printf("Free: %p address\n", __ptr);
   __real_free(__ptr);
}
