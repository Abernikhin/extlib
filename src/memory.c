#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

static size_t count = 0;

void *makePointer(size_t size)
{
    void *ptr = malloc(size);
    count++;
    printf("[alloc %ld] %p\n", count, ptr);
    return ptr;
}

void dropPointer(void *ptr)
{
    if(ptr == NULL) return;
    printf("[ free %ld] %p\n", count, ptr);
    free(ptr);
    count--;
}

void dropUniquePointer(void *ptr)
{
    dropPointer(*((void **)ptr));
    // *(void**)ptr = NULL;
}
