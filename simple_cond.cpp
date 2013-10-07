#include <iostream>

#include "sierra.h"
#include "sierra_ostream.h"

int main() {
    bool varying(4) a = {0, 0, 1, 1};
    bool varying(4) b = {1, 0, 1, 0};
    int varying(4) c = {0, 0, 0, 0};

    if ( a ? b : true ) // {1, 1, 1, 0}
        c = c - 1; // {-1, -1, -1, 0}
    else
        c = c + 1; // {0, 0, 0, 1}

    std::cout << a << std::endl; // {-1, -1, -1, 1}
}
