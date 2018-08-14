#include "test.h"

int foo(int a) {
    return a;
}

int main()
{
    int a = 1234;
    a = foo(a);

    return 0;
}

// $RESULT: 255 = 0b1111
