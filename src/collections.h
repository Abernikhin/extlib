#ifndef _Collection_H_
#define _Collection_H_

#include <string.h>

char *StringDuplicate(char *);

#define String unique char *
#define string(txt) StringDuplicate(txt)
#define stringEq(__s1, __s2) strcmp(__s1, __s2) == 0
#define concat(__s1, __s2)                                                     \
    ({                                                                         \
        char *dst =                                                            \
            makePointer(sizeof(char[strlen(__s1) + strlen(__s2) + 1]));        \
        dst[0] = '\0';                                                         \
        strcat(dst, __s1);                                                     \
        strcat(dst, __s2);                                                     \
        dst;                                                                   \
    })

#endif
