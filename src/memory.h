#ifndef _Memory_H_
#define _Memory_H_

#include <stddef.h>

#define pointer(type)                                                          \
    struct Pointer_##type                                                      \
    {                                                                          \
        type *super;                                                           \
        size_t ptr;                                                            \
    }

size_t makePointer(size_t);
void dropPointer(size_t);
void *getByPointer(size_t);
void clearMemory();
void showMemory();

#define make(type)                                                             \
    (struct Pointer_##type) { NULL, makePointer(sizeof(type)) }
#define drop(obj) dropPointer(obj.ptr)
#define get(obj) *(typeof(obj.super))getByPointer(obj.ptr)

#endif
