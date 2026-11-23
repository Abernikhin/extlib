#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t count = 0;

void *makePointer(size_t size)
{
    void *ptr = malloc(size);
    count++;
    printf("[alloc %ld] %p\n", count, ptr);
    return ptr;
}

char* StringDuplicate(char* txt) {
    char *ptr = strdup(txt);
    count++;
    printf("[alloc %ld] %p\n", count, ptr);
    return ptr;
}

void dropPointer(void *ptr)
{
    if (ptr == NULL) {
        printf("[ free %ld] %p\n", count, ptr);
        count--;
        return;
    }
    printf("[ free %ld] %p\n", count, ptr);
    free(ptr);
    count--;
}

void dropUniquePointer(void *ptr) { dropPointer(*((void **)ptr)); }

typedef struct sharedBlock
{
    size_t count;
} SharedBlock;

void setupBlock(void *ptr)
{
    SharedBlock *b = (SharedBlock*)ptr;
    b->count = 1;
}

void *makeSharedPointer(size_t size)
{
    void *block = malloc(sizeof(SharedBlock) + size);
    if (block == NULL)
        return NULL;

    setupBlock(block);
    return (char *)block + sizeof(SharedBlock);
}

void dropSharedPointer(void *ptr) {
    void* obj = *(void**)ptr;
    if (obj == NULL)
        return;

    SharedBlock* b = (SharedBlock*)((char *)obj - sizeof(SharedBlock));
    b->count--;
    printf("drop owner\n");
    if(b->count == 0) {
        printf("drop shared data\n");
        free(b);
    }
    *(void**)ptr = NULL;
}

void* shareSharedPointer(void *ptr) {
    void* obj = ptr;
    if (obj == NULL)
        return NULL;

    SharedBlock* b = (SharedBlock*)((char *)obj - sizeof(SharedBlock));
    b->count++;
    return ptr;
}
