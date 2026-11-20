#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

static void **table = NULL;
static size_t capacity = 32;
static size_t count = 0;
static size_t first = 0;

static void findNewFirst()
{
    for (size_t i = first; i < count; i++)
    {
        if (table[i] == NULL)
        {
            first = i;
            return;
        }
    }
}

static void extend(size_t size)
{
    void **temp = (void **)realloc(table, sizeof(void *) * (size));
    if(!temp) return;
    if (temp)
        table = temp;
    for (size_t i = count; i < capacity; i++)
    {
        table[i] = NULL;
    }
}

size_t makePointer(size_t size)
{
    if (!table || count == capacity)
    {
        extend(capacity);
    }

    size_t result = count;

    if (!(count == first))
    {
        result = first;
        findNewFirst();
    } else{ count++; first++; }

    table[result] = malloc(size);

    if (count == capacity)
    {
        extend((capacity *= 2));
    }

    return result;
}

void dropPointer(size_t ptr)
{
    if(ptr > capacity) return;
    free(table[ptr]);
    table[ptr] = NULL;
    first = ptr;
}

void* getByPointer(size_t ptr) {
    if(ptr > count) return NULL;
    return table[ptr];
} 

void clearMemory()
{
    for (size_t i = 0; i < count; i++)
    {
        free(table[i]);
    }
    free(table);
    table = NULL;
}

void showMemory()
{
    if(!table) return;
    for (size_t i = 0; i < capacity; i++)
    {
        if(table[i] == NULL) printf("[%ld]: NULL\n", i);
        else printf("[%ld]: %ld\n", i, *((size_t*)table[i]));
    }
}
