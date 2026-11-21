#ifndef _Memory_H_
#define _Memory_H_

#include <stddef.h>

void *makePointer(size_t);
void dropPointer(void *);
void dropUniquePointer(void *);

#define make(type) ((type*)makePointer(sizeof(type)))
#define drop(obj) dropPointer(obj)
#define unique __attribute__((cleanup(dropUniquePointer)))
#define move(obj) ({ typeof(obj) ptr = obj; obj = NULL; ptr; })

#endif
