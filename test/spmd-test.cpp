#include "sierra_ostream.h"

#include <iostream>

spmd(4)
int varying(4) add(int varying(4) a, int varying(4) b) {
        return a + b;
}

int main() {
    int varying(4) a = 23;
    int varying(4) b = {0, 1, 23, 42};

    if (a < b)
        a = add(a, b);

    std::cout << a << std::endl;
}

