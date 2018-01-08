#include "test.h"
#include <stdlib.h>

template<typename T, int Size>
T varying(Size) a;

template<typename T, int Size>
void foo(void) {
    a<T, Size> = 42;
}

int main(void) {
    int varying(4) b;
    foo<int, 4>();
    b = a<int, 4>;
    return 0;
}

