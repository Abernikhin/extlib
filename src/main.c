
#include "memory.h"

int main() {
   
    unique int* i = make(int);
    unique int* j = move(i);
    unique int* k = move(j);

    return 0;
}
