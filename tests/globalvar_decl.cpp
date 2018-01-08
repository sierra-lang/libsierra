#include "test.h"

int varying(4) foo;
//void bar(int varying(4) a);

int main() {
    foo;
    return 0;
}

// $RESULT: 15 = 0b1111
