#ifndef _Memory_H_
#define _Memory_H_

#include <stddef.h>

void *makePointer(size_t);
void setupBlock(void *);
void *makeSharedPointer(size_t);
void *shareSharedPointer(void*);
void dropPointer(void *);
void dropUniquePointer(void *);
void dropSharedPointer(void *);

#define make(type) ((type *)makePointer(sizeof(type)))
#define makeShared(type) ((type *)makeSharedPointer(sizeof(type)))
#define drop(obj) dropPointer(obj)
#define unique __attribute__((cleanup(dropUniquePointer)))
#define shared __attribute__((cleanup(dropSharedPointer)))
#define move(obj)                                                              \
    ({                                                                         \
        typeof(obj) ptr = obj;                                                 \
        obj = NULL;                                                            \
        ptr;                                                                   \
    })
#define share(obj) (typeof(obj))shareSharedPointer(obj);

#endif
