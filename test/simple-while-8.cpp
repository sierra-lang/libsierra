#include "sierra.h"
//#include <iostream>

int varying(8) f() {
    int varying(8) i = 0;

    while (i < 2) {
        i = i + 1;
    }

    return i;
}

int main() {
    f();
}
