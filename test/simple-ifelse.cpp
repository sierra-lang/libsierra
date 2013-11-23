#include <iostream>

#include "sierra.h"
#include "sierra_ostream.h"

int main() {
    int varying(4) a = {0, 1, 2, 3};
    int varying(4) b = 2;

    if (a < b)
        a = a - 1;
    else
        a = a + 1;

    std::cout << a << std::endl;
}
