#include "test.h"

int foo(int a) {
    return a;
}

int main()
{
    int varying(4) a = {1, 2, 3, 4};
    //int a = 1234;
    a = foo(a);

    return (unify(a, 1, 2, 3, 4));
    //return 0;
}

// $RESULT: 255 = 0b1111
