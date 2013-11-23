#include "sierra/ostream.h"

#define L 4
#include "sierra/math.h"

#include <iostream>

using namespace sierra;

int main() {
    float varying(4) f = {0, 2, 3, 4};
    float varying(4) e = exp(f);
    std::cout << e << std::endl;
}
