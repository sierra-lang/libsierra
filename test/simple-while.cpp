#include "sierra_ostream.h"
#include <iostream>

int varying(4) f() {
    int varying(4) i = 0;

    int varying(4) res = 42;
    while (i < (int varying(4)){ 23, 42, 7, 666 }) {
        int varying(4) j = i;
        res += j;
        i = i + 1;
    }

    return res;
}

int main() {
    std::cout << f() << std::endl;
}
